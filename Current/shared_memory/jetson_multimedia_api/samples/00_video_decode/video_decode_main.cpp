/*
 * Copyright (c) 2016-2023, NVIDIA CORPORATION. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of NVIDIA CORPORATION nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "NvApplicationProfiler.h"
#include "NvUtils.h"
#include <errno.h>
#include <fstream>
#include <iostream>
#include <linux/videodev2.h>
#include <malloc.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <vulkan/vulkan.h>
#include "video_decode.h"
#include <bitset>
#include <set>

#define TEST_ERROR(cond, str, label) if(cond) { \
                                        cerr << str << endl; \
                                        error = 1; \
                                        goto label; }

#define MICROSECOND_UNIT 1000000
#define CHUNK_SIZE 4000000
#define MIN(a,b) (((a) < (b)) ? (a) : (b))

#define IS_NAL_UNIT_START(buffer_ptr) (!buffer_ptr[0] && !buffer_ptr[1] && \
        !buffer_ptr[2] && (buffer_ptr[3] == 1))

#define IS_NAL_UNIT_START1(buffer_ptr) (!buffer_ptr[0] && !buffer_ptr[1] && \
        (buffer_ptr[2] == 1))

#define H264_NAL_UNIT_CODED_SLICE  1
#define H264_NAL_UNIT_CODED_SLICE_IDR  5

#define HEVC_NUT_TRAIL_N  0
#define HEVC_NUT_RASL_R  9
#define HEVC_NUT_BLA_W_LP  16
#define HEVC_NUT_CRA_NUT  21

#define IVF_FILE_HDR_SIZE   32
#define IVF_FRAME_HDR_SIZE  12

#define IS_H264_NAL_CODED_SLICE(buffer_ptr) ((buffer_ptr[0] & 0x1F) == H264_NAL_UNIT_CODED_SLICE)
#define IS_H264_NAL_CODED_SLICE_IDR(buffer_ptr) ((buffer_ptr[0] & 0x1F) == H264_NAL_UNIT_CODED_SLICE_IDR)

#define IS_MJPEG_START(buffer_ptr) (buffer_ptr[0] == 0xFF && buffer_ptr[1] == 0xD8)
#define IS_MJPEG_END(buffer_ptr) (buffer_ptr[0] == 0xFF && buffer_ptr[1] == 0xD9)

#define GET_H265_NAL_UNIT_TYPE(buffer_ptr) ((buffer_ptr[0] & 0x7E) >> 1)

using namespace std;

/**
  * Read the input NAL unit for h264/H265/Mpeg2/Mpeg4 decoder.
  *
  * @param stream            : Input stream
  * @param buffer            : NvBuffer pointer
  * @param parse_buffer      : parse buffer pointer
  * @param parse_buffer_size : chunk size
  * @param ctx               : Decoder context
  */
static int
read_decoder_input_nalu(ifstream * stream, NvBuffer * buffer,
        char *parse_buffer, streamsize parse_buffer_size, context_t * ctx)
{
    /* Length is the size of the buffer in bytes. */
    char *buffer_ptr = (char *) buffer->planes[0].data;
    uint8_t h265_nal_unit_type;
    char *stream_ptr;
    bool nalu_found = false;
    uint16_t h265_nal_unit_header;

    streamsize bytes_read;
    streamsize stream_initial_pos = stream->tellg();

    stream->read(parse_buffer, parse_buffer_size);
    bytes_read = stream->gcount();

    if (bytes_read == 0)
    {
        ctx->flag_copyts = false;
        return buffer->planes[0].bytesused = 0;
    }

    /* Find the first NAL unit in the buffer. */
    stream_ptr = parse_buffer;
    while ((stream_ptr - parse_buffer) < (bytes_read - 3))
    {
        nalu_found = IS_NAL_UNIT_START(stream_ptr);
        if (nalu_found)
        {
            memcpy(buffer_ptr, stream_ptr, 4);
            buffer_ptr += 4;
            buffer->planes[0].bytesused = 4;
            stream_ptr += 4;
            break;
        }

        nalu_found = IS_NAL_UNIT_START1(stream_ptr);
        if (nalu_found)
        {
            memcpy(buffer_ptr, stream_ptr, 3);
            buffer_ptr += 3;
            buffer->planes[0].bytesused = 3;
            stream_ptr += 3;
            break;
        }
        stream_ptr++;
    }

    /* Reached end of buffer but could not find NAL unit. */
    if (!nalu_found)
    {
        ctx->flag_copyts = false;
        cerr << "Could not read nal unit from file. EOF or file corrupted"
            << endl;
        return -1;
    }

    if (ctx->copy_timestamp)
    {
      if (ctx->decoder_pixfmt == V4L2_PIX_FMT_H264) {
        if ((IS_H264_NAL_CODED_SLICE(stream_ptr)) ||
            (IS_H264_NAL_CODED_SLICE_IDR(stream_ptr))) {
          /* Check for first_mb_in_slice parameter to find first slice of the video frame.
           * If first_mb_in_slice equal to 0 then the current slice is the very first slice
           * in a picture.
           */
          ctx->flag_copyts = (stream_ptr[1] & 0x80) ? true : false;
        }
        else {
          ctx->flag_copyts = false;
        }
      } else if (ctx->decoder_pixfmt == V4L2_PIX_FMT_H265) {
        h265_nal_unit_header = (stream_ptr[0] << 8) | stream_ptr[1];
        h265_nal_unit_type = (h265_nal_unit_header & 0x7e00) >> 9;

        if ((h265_nal_unit_type >= HEVC_NUT_TRAIL_N && h265_nal_unit_type <= HEVC_NUT_RASL_R) ||
            (h265_nal_unit_type >= HEVC_NUT_BLA_W_LP && h265_nal_unit_type <= HEVC_NUT_CRA_NUT)) {
          /* Check for first_slice_segment_in_pic_flag to find first slice of the video frame.
           * first_slice_segment_in_pic_flag equal to 1 specifies that the slice segment is the
           * first slice segment of the picture in decoding order.
           */
          ctx->flag_copyts = (stream_ptr[2] >> 7) ? true : false;
        }
        else {
          ctx->flag_copyts = false;
        }
      }
    }

    /* Copy bytes till the next NAL unit is found. */
    while ((stream_ptr - parse_buffer) < (bytes_read - 3))
    {
        if (IS_NAL_UNIT_START(stream_ptr) || IS_NAL_UNIT_START1(stream_ptr))
        {
            streamsize seekto = stream_initial_pos +
                    (stream_ptr - parse_buffer);
            if(stream->eof())
            {
                stream->clear();
            }
            stream->seekg(seekto, stream->beg);
            return 0;
        }
        *buffer_ptr = *stream_ptr;
        buffer_ptr++;
        stream_ptr++;
        buffer->planes[0].bytesused++;
    }

    memcpy(buffer_ptr, stream_ptr, 3);
    buffer_ptr += 3;
    buffer->planes[0].bytesused += 3;
    stream_ptr += 3;

    /* Reached end of buffer but could not find NAL unit. */
    cerr << "Could not read nal unit from file. EOF or file corrupted"
            << endl;
    return -1;
}

/**
  * Read the input chunks for h264/H265/Mpeg2/Mpeg4 decoder.
  *
  * @param stream : Input stream
  * @param buffer : NvBuffer pointer
  */
static int
read_decoder_input_chunk(ifstream * stream, NvBuffer * buffer)
{
    /* Length is the size of the buffer in bytes */
    streamsize bytes_to_read = MIN(CHUNK_SIZE, buffer->planes[0].length);

    stream->read((char *) buffer->planes[0].data, bytes_to_read);
    /* NOTE: It is necessary to set bytesused properly, so that decoder knows how
             many bytes in the buffer are valid. */
    buffer->planes[0].bytesused = stream->gcount();
    if(buffer->planes[0].bytesused == 0)
    {
        stream->clear();
        stream->seekg(0,stream->beg);
    }
    return 0;
}

/**
  * Read the input chunks for MJPEG decoder.
  *
  * @param stream : Input filestream
  * @param buffer : NvBuffer pointer
  */
static int
read_mjpeg_decoder_input(ifstream * stream, NvBuffer * buffer)
{
    char *buffer_ptr = (char *)buffer->planes[0].data;
    stream->read(buffer_ptr,2);
            buffer->planes[0].bytesused += stream->gcount();
    if (IS_MJPEG_START(buffer_ptr))
    {
        while (!IS_MJPEG_END(buffer_ptr))
        {
            buffer_ptr+=2;
            stream->read(buffer_ptr,2);
            buffer->planes[0].bytesused += stream->gcount();
        }
    }

    if(buffer->planes[0].bytesused == 0)
    {
        stream->clear();
        stream->seekg(0,stream->beg);
    }

    return 0;
}

/**
  * Read the input chunks for Vp8/Vp9/AV1 decoder.
  *
  * @param ctx    : Decoder context
  * @param buffer : NvBuffer pointer
  */
static int
read_vpx_decoder_input_chunk(context_t *ctx, NvBuffer * buffer)
{
    ifstream *stream = ctx->in_file[0];
    int Framesize;
    unsigned char *bitstreambuffer = (unsigned char *)buffer->planes[0].data;
    if (ctx->vp9_file_header_flag == 0)
    {
        stream->read((char *) buffer->planes[0].data, IVF_FILE_HDR_SIZE);
        if (stream->gcount() !=  IVF_FILE_HDR_SIZE)
        {
            cerr << "Couldn't read IVF FILE HEADER" << endl;
            return -1;
        }
        if (!((bitstreambuffer[0] == 'D') && (bitstreambuffer[1] == 'K') &&
                    (bitstreambuffer[2] == 'I') && (bitstreambuffer[3] == 'F')))
        {
            cerr << "It's not a valid IVF file \n" << endl;
            return -1;
        }
        cout << "It's a valid IVF file" << endl;
        ctx->vp9_file_header_flag = 1;
        if (ctx->copy_timestamp &&
            ctx->decoder_pixfmt == V4L2_PIX_FMT_AV1)
        {
             ctx->flag_copyts = true;
        }
    }
    stream->read((char *) buffer->planes[0].data, IVF_FRAME_HDR_SIZE);

    if (!stream->gcount())
    {
        cout << "End of stream" << endl;
        return 0;
    }

    if (stream->gcount() != IVF_FRAME_HDR_SIZE)
    {
        cerr << "Couldn't read IVF FRAME HEADER" << endl;
        return -1;
    }
    Framesize = (bitstreambuffer[3]<<24) + (bitstreambuffer[2]<<16) +
        (bitstreambuffer[1]<<8) + bitstreambuffer[0];
    buffer->planes[0].bytesused = Framesize;
    stream->read((char *) buffer->planes[0].data, Framesize);
    if (stream->gcount() != Framesize)
    {
        cerr << "Couldn't read Framesize" << endl;
        return -1;
    }
    return 0;
}

/**
  * Exit on error.
  *
  * @param ctx : Decoder context
  */
static void
abort(context_t *ctx)
{
    ctx->got_error = true;
    ctx->dec->abort();
}

/**
  * Report decoder input header error metadata.
  *
  * @param ctx             : Decoder context
  * @param input_metadata  : Pointer to decoder input header error metadata struct
  */
static int
report_input_metadata(context_t *ctx, v4l2_ctrl_videodec_inputbuf_metadata *input_metadata)
{
    int ret = -1;
    uint32_t frame_num = ctx->dec->output_plane.getTotalDequeuedBuffers() - 1;

    /* NOTE: Bits represent types of error as defined with v4l2_videodec_input_error_type. */
    if (input_metadata->nBitStreamError & V4L2_DEC_ERROR_SPS) {
      cout << "Frame " << frame_num << " BitStreamError : ERROR_SPS " << endl;
    } else if (input_metadata->nBitStreamError & V4L2_DEC_ERROR_PPS) {
      cout << "Frame " << frame_num << " BitStreamError : ERROR_PPS " << endl;
    } else if (input_metadata->nBitStreamError & V4L2_DEC_ERROR_SLICE_HDR) {
      cout << "Frame " << frame_num << " BitStreamError : ERROR_SLICE_HDR " << endl;
    } else if (input_metadata->nBitStreamError & V4L2_DEC_ERROR_MISSING_REF_FRAME) {
      cout << "Frame " << frame_num << " BitStreamError : ERROR_MISSING_REF_FRAME " << endl;
    } else if (input_metadata->nBitStreamError & V4L2_DEC_ERROR_VPS) {
      cout << "Frame " << frame_num << " BitStreamError : ERROR_VPS " << endl;
    } else {
      cout << "Frame " << frame_num << " BitStreamError : ERROR_None " << endl;
      ret = 0;
    }
    return ret;
}

/**
  * Report decoder output metadata.
  *
  * @param ctx      : Decoder context
  * @param metadata : Pointer to decoder output metadata struct
  */
static void
report_metadata(context_t *ctx, v4l2_ctrl_videodec_outputbuf_metadata *metadata)
{
    uint32_t frame_num = ctx->dec->capture_plane.getTotalDequeuedBuffers() - 1;

    cout << "Frame " << frame_num << endl;

    if (metadata->bValidFrameStatus)
    {
        if (ctx->decoder_pixfmt == V4L2_PIX_FMT_H264)
        {
            /* metadata for H264 input stream. */
            switch(metadata->CodecParams.H264DecParams.FrameType)
            {
                case 0:
                    cout << "FrameType = B" << endl;
                    break;
                case 1:
                    cout << "FrameType = P" << endl;
                    break;
                case 2:
                    cout << "FrameType = I";
                    if (metadata->CodecParams.H264DecParams.dpbInfo.currentFrame.bIdrFrame)
                    {
                        cout << " (IDR)";
                    }
                    cout << endl;
                    break;
            }
            cout << "nActiveRefFrames = " << metadata->CodecParams.H264DecParams.dpbInfo.nActiveRefFrames << endl;
        }

        if (ctx->decoder_pixfmt == V4L2_PIX_FMT_H265)
        {
            /* metadata for HEVC input stream. */
            switch(metadata->CodecParams.HEVCDecParams.FrameType)
            {
                case 0:
                    cout << "FrameType = B" << endl;
                    break;
                case 1:
                    cout << "FrameType = P" << endl;
                    break;
                case 2:
                    cout << "FrameType = I";
                    if (metadata->CodecParams.HEVCDecParams.dpbInfo.currentFrame.bIdrFrame)
                    {
                        cout << " (IDR)";
                    }
                    cout << endl;
                    break;
            }
            cout << "nActiveRefFrames = " << metadata->CodecParams.HEVCDecParams.dpbInfo.nActiveRefFrames << endl;
        }

        if (metadata->FrameDecStats.DecodeError)
        {
            /* decoder error status metadata. */
            v4l2_ctrl_videodec_statusmetadata *dec_stats =
                &metadata->FrameDecStats;
            cout << "ErrorType="  << dec_stats->DecodeError << " Decoded MBs=" <<
                dec_stats->DecodedMBs << " Concealed MBs=" <<
                dec_stats->ConcealedMBs << endl;
        }
    }
    else
    {
        cout << "No valid metadata for frame" << endl;
    }
}

/**
  * Query and Set Capture plane.
  *
  * @param ctx : Decoder context
  */
static void
query_and_set_capture(context_t * ctx)
{
    NvVideoDecoder *dec = ctx->dec;
    struct v4l2_format format;
    struct v4l2_crop crop;
    int32_t min_dec_capture_buffers;
    int ret = 0;
    int error = 0;
    uint32_t window_width;
    uint32_t window_height;
    uint32_t sar_width;
    uint32_t sar_height;
    NvBufSurfaceColorFormat pix_format;
    NvBufSurf::NvCommonAllocateParams params;
    NvBufSurf::NvCommonAllocateParams capParams;

    /* Get capture plane format from the decoder.
       This may change after resolution change event.
       Refer ioctl VIDIOC_G_FMT */
    ret = dec->capture_plane.getFormat(format);
    TEST_ERROR(ret < 0,
               "Error: Could not get format from decoder capture plane", error);

    /* Get the display resolution from the decoder.
       Refer ioctl VIDIOC_G_CROP */
    ret = dec->capture_plane.getCrop(crop);
    TEST_ERROR(ret < 0,
               "Error: Could not get crop from decoder capture plane", error);

    cout << "Video Resolution: " << crop.c.width << "x" << crop.c.height
        << endl;
    ctx->display_height = crop.c.height;
    ctx->display_width = crop.c.width;

    /* Get the Sample Aspect Ratio (SAR) width and height */
    ret = dec->getSAR(sar_width, sar_height);
    cout << "Video SAR width: " << sar_width << " SAR height: " << sar_height << endl;
    if(ctx->dst_dma_fd != -1)
    {
        ret = NvBufSurf::NvDestroy(ctx->dst_dma_fd);
        ctx->dst_dma_fd = -1;
        TEST_ERROR(ret < 0, "Error: Error in BufferDestroy", error);
    }
    /* Create output buffer for transform. */
    params.memType = NVBUF_MEM_SURFACE_ARRAY;
    params.width = crop.c.width;
    params.height = crop.c.height;
    if (ctx->vkRendering)
    {
        /* Foreign FD in rmapi_tegra is imported as block linear kind by default and
         * there is no way right now in our driver to know the kind at the time of
         * import
         * */
        params.layout = NVBUF_LAYOUT_BLOCK_LINEAR;
    }
    else
        params.layout = NVBUF_LAYOUT_PITCH;
    if (ctx->out_pixfmt == 1)
      params.colorFormat = NVBUF_COLOR_FORMAT_NV12;
    else if (ctx->out_pixfmt == 2)
      params.colorFormat = NVBUF_COLOR_FORMAT_YUV420;
    else if (ctx->out_pixfmt == 3)
      params.colorFormat = NVBUF_COLOR_FORMAT_NV16;
    else if (ctx->out_pixfmt == 4)
      params.colorFormat = NVBUF_COLOR_FORMAT_NV24;

    params.memtag = NvBufSurfaceTag_VIDEO_CONVERT;
    if (ctx->vkRendering)
        params.colorFormat = NVBUF_COLOR_FORMAT_RGBA;

    ret = NvBufSurf::NvAllocate(&params, 1, &ctx->dst_dma_fd);
    TEST_ERROR(ret == -1, "create dmabuf failed", error);

    if (!ctx->disable_rendering)
    {
        /* Destroy the old instance of renderer as resolution might have changed. */
        if (ctx->vkRendering)
        {
            delete ctx->vkRenderer;
        } else {
            delete ctx->eglRenderer;
        }

        if (ctx->fullscreen)
        {
            /* Required for fullscreen. */
            window_width = window_height = 0;
        }
        else if (ctx->window_width && ctx->window_height)
        {
            /* As specified by user on commandline. */
            window_width = ctx->window_width;
            window_height = ctx->window_height;
        }
        else
        {
            /* Resolution got from the decoder. */
            window_width = crop.c.width;
            window_height = crop.c.height;
        }

        if (!ctx->vkRendering)
        {
            /* If height or width are set to zero, EglRenderer creates a fullscreen
               window for rendering. */
            ctx->eglRenderer =
                NvEglRenderer::createEglRenderer("renderer0", window_width,
                                           window_height, ctx->window_x,
                                           ctx->window_y);
            TEST_ERROR(!ctx->eglRenderer,
                   "Error in setting up of egl renderer. "
                   "Check if X is running or run with --disable-rendering",
                   error);
            if (ctx->stats)
            {
                /* Enable profiling for renderer if stats are requested. */
                ctx->eglRenderer->enableProfiling();
            }
            ctx->eglRenderer->setFPS(ctx->fps);
        } else {
            ctx->vkRenderer = NvVulkanRenderer::createVulkanRenderer("renderer0", window_width,
                                           window_height, ctx->window_x,
                                           ctx->window_y);
            TEST_ERROR(!ctx->vkRenderer,
                   "Error in setting up of vulkan renderer. "
                   "Check if X is running or run with --disable-rendering",
                   error);
            ctx->vkRenderer->setSize(window_width, window_height);
            ctx->vkRenderer->initVulkan();
        }
    }

    /* deinitPlane unmaps the buffers and calls REQBUFS with count 0 */
    dec->capture_plane.deinitPlane();
    if(ctx->capture_plane_mem_type == V4L2_MEMORY_DMABUF)
    {
        for(int index = 0 ; index < ctx->numCapBuffers ; index++)
        {
            if(ctx->dmabuff_fd[index] != 0)
            {
                ret = NvBufSurf::NvDestroy(ctx->dmabuff_fd[index]);
                TEST_ERROR(ret < 0, "Error: Error in BufferDestroy", error);
            }
        }
    }

    /* Not necessary to call VIDIOC_S_FMT on decoder capture plane.
       But decoder setCapturePlaneFormat function updates the class variables */
    ret = dec->setCapturePlaneFormat(format.fmt.pix_mp.pixelformat,
                                     format.fmt.pix_mp.width,
                                     format.fmt.pix_mp.height);
    TEST_ERROR(ret < 0, "Error in setting decoder capture plane format", error);

    ctx->video_height = format.fmt.pix_mp.height;
    ctx->video_width = format.fmt.pix_mp.width;
    /* Get the minimum buffers which have to be requested on the capture plane. */
    ret = dec->getMinimumCapturePlaneBuffers(min_dec_capture_buffers);
    TEST_ERROR(ret < 0,
               "Error while getting value of minimum capture plane buffers",
               error);

    /* Request (min + extra) buffers, export and map buffers. */
    if(ctx->capture_plane_mem_type == V4L2_MEMORY_MMAP)
    {
        /* Request, Query and export decoder capture plane buffers.
           Refer ioctl VIDIOC_REQBUFS, VIDIOC_QUERYBUF and VIDIOC_EXPBUF */
        ret =
            dec->capture_plane.setupPlane(V4L2_MEMORY_MMAP,
                                          min_dec_capture_buffers + ctx->extra_cap_plane_buffer, false,
                                          false);
        TEST_ERROR(ret < 0, "Error in decoder capture plane setup", error);
    }
    else if(ctx->capture_plane_mem_type == V4L2_MEMORY_DMABUF)
    {
        /* Set colorformats for relevant colorspaces. */
        switch(format.fmt.pix_mp.colorspace)
        {
            case V4L2_COLORSPACE_SMPTE170M:
                if (format.fmt.pix_mp.quantization == V4L2_QUANTIZATION_DEFAULT)
                {
                    cout << "Decoder colorspace ITU-R BT.601 with standard range luma (16-235)" << endl;
                    pix_format = NVBUF_COLOR_FORMAT_NV12;
                }
                else
                {
                    cout << "Decoder colorspace ITU-R BT.601 with extended range luma (0-255)" << endl;
                    pix_format = NVBUF_COLOR_FORMAT_NV12_ER;
                }
                break;
            case V4L2_COLORSPACE_REC709:
                if (format.fmt.pix_mp.quantization == V4L2_QUANTIZATION_DEFAULT)
                {
                    cout << "Decoder colorspace ITU-R BT.709 with standard range luma (16-235)" << endl;
                    pix_format =  NVBUF_COLOR_FORMAT_NV12_709;
                }
                else
                {
                    cout << "Decoder colorspace ITU-R BT.709 with extended range luma (0-255)" << endl;
                    pix_format = NVBUF_COLOR_FORMAT_NV12_709_ER;
                }
                break;
            case V4L2_COLORSPACE_BT2020:
                {
                    cout << "Decoder colorspace ITU-R BT.2020" << endl;
                    pix_format = NVBUF_COLOR_FORMAT_NV12_2020;
                }
                break;
            default:
                cout << "supported colorspace details not available, use default" << endl;
                if (format.fmt.pix_mp.quantization == V4L2_QUANTIZATION_DEFAULT)
                {
                    cout << "Decoder colorspace ITU-R BT.601 with standard range luma (16-235)" << endl;
                    pix_format = NVBUF_COLOR_FORMAT_NV12;
                }
                else
                {
                    cout << "Decoder colorspace ITU-R BT.601 with extended range luma (0-255)" << endl;
                    pix_format = NVBUF_COLOR_FORMAT_NV12_ER;
                }
                break;
        }

        ctx->numCapBuffers = min_dec_capture_buffers + ctx->extra_cap_plane_buffer;

        capParams.memType = NVBUF_MEM_SURFACE_ARRAY;
        capParams.width = crop.c.width;
        capParams.height = crop.c.height;
        capParams.layout = NVBUF_LAYOUT_BLOCK_LINEAR;
        capParams.memtag = NvBufSurfaceTag_VIDEO_DEC;

        if (format.fmt.pix_mp.pixelformat  == V4L2_PIX_FMT_NV24M)
          pix_format = NVBUF_COLOR_FORMAT_NV24;
        else if (format.fmt.pix_mp.pixelformat  == V4L2_PIX_FMT_NV24_10LE)
          pix_format = NVBUF_COLOR_FORMAT_NV24_10LE;
        if (ctx->decoder_pixfmt == V4L2_PIX_FMT_MJPEG)
        {
            capParams.layout = NVBUF_LAYOUT_PITCH;
            if (format.fmt.pix_mp.pixelformat == V4L2_PIX_FMT_YUV422M)
            {
                pix_format = NVBUF_COLOR_FORMAT_YUV422;
            }
            else
            {
                pix_format = NVBUF_COLOR_FORMAT_YUV420;
            }
        }

        capParams.colorFormat = pix_format;

        ret = NvBufSurf::NvAllocate(&capParams, ctx->numCapBuffers, ctx->dmabuff_fd);

        TEST_ERROR(ret < 0, "Failed to create buffers", error);
        /* Request buffers on decoder capture plane.
           Refer ioctl VIDIOC_REQBUFS */
        ret = dec->capture_plane.reqbufs(V4L2_MEMORY_DMABUF,ctx->numCapBuffers);
        TEST_ERROR(ret, "Error in request buffers on capture plane", error);
    }

    /* Decoder capture plane STREAMON.
       Refer ioctl VIDIOC_STREAMON */
    ret = dec->capture_plane.setStreamStatus(true);
    TEST_ERROR(ret < 0, "Error in decoder capture plane streamon", error);

    /* Enqueue all the empty decoder capture plane buffers. */
    for (uint32_t i = 0; i < dec->capture_plane.getNumBuffers(); i++)
    {
        struct v4l2_buffer v4l2_buf;
        struct v4l2_plane planes[MAX_PLANES];

        memset(&v4l2_buf, 0, sizeof(v4l2_buf));
        memset(planes, 0, sizeof(planes));

        v4l2_buf.index = i;
        v4l2_buf.m.planes = planes;
        v4l2_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        v4l2_buf.memory = ctx->capture_plane_mem_type;
        if(ctx->capture_plane_mem_type == V4L2_MEMORY_DMABUF)
            v4l2_buf.m.planes[0].m.fd = ctx->dmabuff_fd[i];
        ret = dec->capture_plane.qBuffer(v4l2_buf, NULL);
        TEST_ERROR(ret < 0, "Error Qing buffer at output plane", error);
    }
    cout << "Query and set capture successful" << endl;
    return;

error:
    if (error)
    {
        abort(ctx);
        cerr << "Error in " << __func__ << endl;
    }
}

/**
  * Decoder polling thread loop function.
  *
  * @param args : void arguments
  */
static void *decoder_pollthread_fcn(void *arg)
{

    context_t *ctx = (context_t *) arg;
    v4l2_ctrl_video_device_poll devicepoll;

    cout << "Starting Device Poll Thread " << endl;

    memset(&devicepoll, 0, sizeof(v4l2_ctrl_video_device_poll));

    /* Wait here until you are signalled to issue the Poll call.
       Check if the abort status is set , if so exit.
       Else issue the Poll on the decoder and block.
       When the Poll returns, signal the decoder thread to continue. */

    while (!ctx->got_error && !ctx->dec->isInError())
    {
        /* wait on polling semaphore */
        sem_wait(&ctx->pollthread_sema);

        if (ctx->got_eos)
        {
            cout << "Decoder got eos, exiting poll thread \n";
            return NULL;
        }

        devicepoll.req_events = POLLIN | POLLOUT | POLLERR | POLLPRI;

        /* This call shall wait in the v4l2 decoder library.
           Refer V4L2_CID_MPEG_VIDEO_DEVICE_POLL */
        ctx->dec->DevicePoll(&devicepoll);

        /* We can check the devicepoll.resp_events bitmask to see
           which events are set. */
        sem_post(&ctx->decoderthread_sema);
    }
    return NULL;
}

/**
  * Decoder capture thread loop function.
  *
  * @param args : void arguments
  */
static void *
dec_capture_loop_fcn(void *arg)
{
    context_t *ctx = (context_t *) arg;
    NvVideoDecoder *dec = ctx->dec;
    struct v4l2_event ev;
    int ret;

    cout << "Starting decoder capture loop thread" << endl;
    /* Need to wait for the first Resolution change event, so that
       the decoder knows the stream resolution and can allocate appropriate
       buffers when we call REQBUFS. */
    do
    {
        /* Refer ioctl VIDIOC_DQEVENT */
        ret = dec->dqEvent(ev, 50000);
        if (ret < 0)
        {
            if (errno == EAGAIN)
            {
                cerr <<
                    "Timed out waiting for first V4L2_EVENT_RESOLUTION_CHANGE"
                    << endl;
            }
            else
            {
                cerr << "Error in dequeueing decoder event" << endl;
            }
            abort(ctx);
            break;
        }
    }
    while ((ev.type != V4L2_EVENT_RESOLUTION_CHANGE) && !ctx->got_error);

    /* Received the resolution change event, now can do query_and_set_capture. */
    if (!ctx->got_error)
        query_and_set_capture(ctx);

    /* Exit on error or EOS which is signalled in main() */
    while (!(ctx->got_error || dec->isInError()))
    {
        NvBuffer *dec_buffer;

        /* Check for Resolution change again.
           Refer ioctl VIDIOC_DQEVENT */
        ret = dec->dqEvent(ev, false);
        if (ret == 0)
        {
            switch (ev.type)
            {
                case V4L2_EVENT_RESOLUTION_CHANGE:
                    query_and_set_capture(ctx);
                    continue;
            }
        }

        /* Decoder capture loop */
        while (1)
        {
            struct v4l2_buffer v4l2_buf;
            struct v4l2_plane planes[MAX_PLANES];

            memset(&v4l2_buf, 0, sizeof(v4l2_buf));
            memset(planes, 0, sizeof(planes));
            v4l2_buf.m.planes = planes;

            /* Dequeue a filled buffer. */
            if (dec->capture_plane.dqBuffer(v4l2_buf, &dec_buffer, NULL, 0))
            {
                if (errno == EAGAIN)
                {
                    if (v4l2_buf.flags & V4L2_BUF_FLAG_LAST)
                    {
                        cout << "Got EoS at capture plane" << endl;
                        goto handle_eos;
                    }
                    usleep(1000);
                }
                else
                {
                    abort(ctx);
                    cerr << "Error while calling dequeue at capture plane" <<
                        endl;
                }
                break;
            }

            if (ctx->enable_metadata)
            {
                v4l2_ctrl_videodec_outputbuf_metadata dec_metadata;

                /* Get the decoder output metadata on capture-plane.
                   Refer V4L2_CID_MPEG_VIDEODEC_METADATA */
                ret = dec->getMetadata(v4l2_buf.index, dec_metadata);
                if (ret == 0)
                {
                    report_metadata(ctx, &dec_metadata);
                }
            }

            if (ctx->copy_timestamp && ctx->input_nalu && ctx->stats)
            {
              cout << "[" << v4l2_buf.index << "]" "dec capture plane dqB timestamp [" <<
                  v4l2_buf.timestamp.tv_sec << "s" << v4l2_buf.timestamp.tv_usec << "us]" << endl;
            }

            if (!ctx->disable_rendering && ctx->stats && !ctx->vkRendering)
            {
                /* EglRenderer requires the fd of the 0th plane to render the buffer. */
                if(ctx->capture_plane_mem_type == V4L2_MEMORY_DMABUF)
                    dec_buffer->planes[0].fd = ctx->dmabuff_fd[v4l2_buf.index];

                ctx->eglRenderer->render(dec_buffer->planes[0].fd);
            }

            if (ctx->out_file || (!ctx->disable_rendering && !ctx->stats))
            {
                /* Clip & Stitch can be done by adjusting rectangle. */
                NvBufSurf::NvCommonTransformParams transform_params;
                transform_params.src_top = 0;
                transform_params.src_left = 0;
                transform_params.src_width = ctx->display_width;
                transform_params.src_height = ctx->display_height;
                transform_params.dst_top = 0;
                transform_params.dst_left = 0;
                transform_params.dst_width = ctx->display_width;
                transform_params.dst_height = ctx->display_height;
                transform_params.flag = NVBUFSURF_TRANSFORM_FILTER;
                transform_params.flip = NvBufSurfTransform_None;
                transform_params.filter = NvBufSurfTransformInter_Nearest;
                if(ctx->capture_plane_mem_type == V4L2_MEMORY_DMABUF)
                    dec_buffer->planes[0].fd = ctx->dmabuff_fd[v4l2_buf.index];
                /* Perform Blocklinear to PitchLinear conversion. */
                ret = NvBufSurf::NvTransform(&transform_params, dec_buffer->planes[0].fd, ctx->dst_dma_fd);
                if (ret == -1)
                {
                    cerr << "Transform failed" << endl;
                    break;
                }

                /* Write raw video frame to file. */
                if (!ctx->stats && ctx->out_file)
                {
                    /* Dumping two planes for NV12, NV16, NV24 and three for I420 */
                    dump_dmabuf(ctx->dst_dma_fd, 0, ctx->out_file);
                    dump_dmabuf(ctx->dst_dma_fd, 1, ctx->out_file);
                    if (ctx->out_pixfmt == 2)
                    {
                        dump_dmabuf(ctx->dst_dma_fd, 2, ctx->out_file);
                    }
                }

                if (!ctx->stats && !ctx->disable_rendering)
                {
                    if (ctx->vkRendering) {
                        ctx->vkRenderer->render(ctx->dst_dma_fd);
                    } else {
                        ctx->eglRenderer->render(ctx->dst_dma_fd);
                    }
                }

                /* If not writing to file, Queue the buffer back once it has been used. */
                if(ctx->capture_plane_mem_type == V4L2_MEMORY_DMABUF)
                    v4l2_buf.m.planes[0].m.fd = ctx->dmabuff_fd[v4l2_buf.index];
                if (dec->capture_plane.qBuffer(v4l2_buf, NULL) < 0)
                {
                    abort(ctx);
                    cerr <<
                        "Error while queueing buffer at decoder capture plane"
                        << endl;
                    break;
                }
            }
            else
            {
                /* If not writing to file, Queue the buffer back once it has been used. */
                if(ctx->capture_plane_mem_type == V4L2_MEMORY_DMABUF)
                    v4l2_buf.m.planes[0].m.fd = ctx->dmabuff_fd[v4l2_buf.index];
                if (dec->capture_plane.qBuffer(v4l2_buf, NULL) < 0)
                {
                    abort(ctx);
                    cerr <<
                        "Error while queueing buffer at decoder capture plane"
                        << endl;
                    break;
                }
            }
        }
    }
handle_eos:
    cout << "Exiting decoder capture loop thread" << endl;
    return NULL;
}

/**
  * Set the default values for decoder context members.
  *
  * @param ctx : Decoder context
  */
static void
set_defaults(context_t * ctx)
{
    memset(ctx, 0, sizeof(context_t));
    ctx->fullscreen = false;
    ctx->window_height = 0;
    ctx->window_width = 0;
    ctx->window_x = 0;
    ctx->window_y = 0;
    ctx->out_pixfmt = 1;
    ctx->fps = 30;
    ctx->output_plane_mem_type = V4L2_MEMORY_MMAP;
    ctx->capture_plane_mem_type = V4L2_MEMORY_DMABUF;
    ctx->vp9_file_header_flag = 0;
    ctx->vp8_file_header_flag = 0;
    ctx->stress_test = 1;
    ctx->copy_timestamp = false;
    ctx->flag_copyts = false;
    ctx->start_ts = 0;
    ctx->file_count = 1;
    ctx->dec_fps = 30;
    ctx->dst_dma_fd = -1;
    ctx->bLoop = false;
    ctx->bQueue = false;
    ctx->loop_count = 0;
    ctx->max_perf = 0;
    ctx->extra_cap_plane_buffer = 1;
    ctx->blocking_mode = 1;
    pthread_mutex_init(&ctx->queue_lock, NULL);
    pthread_cond_init(&ctx->queue_cond, NULL);
}

/**
  * Decode processing function for non-blocking mode.
  *
  * @param ctx               : Decoder context
  * @param eos               : end of stream
  * @param current_file      : current file
  * @param current_loop      : iterator count
  * @param nalu_parse_buffer : input parsed nal unit
  */
static bool decoder_proc_nonblocking(context_t &ctx, bool eos, uint32_t current_file,
                    int current_loop, char *nalu_parse_buffer)
{
    /*  NOTE: In non-blocking mode, we will have this function do below things:
              1) Issue signal to PollThread so it starts Poll and wait until we are signalled.
              2) After we are signalled, it means there is something to dequeue, either output plane
                 or capture plane or there's an event.
              3) Try dequeuing from all three and then act appropriately.
              4) After enqueuing go back to the same loop. */

    /* Since all the output plane buffers have been queued, we first need to
       dequeue a buffer from output plane before we can read new data into it
       and queue it again. */
    int allow_DQ = true;
    int ret = 0;
    struct v4l2_buffer temp_buf;
    struct v4l2_event ev;

    while (!ctx.got_error && !ctx.dec->isInError())
    {
        struct v4l2_buffer v4l2_output_buf;
        struct v4l2_plane output_planes[MAX_PLANES];

        struct v4l2_buffer v4l2_capture_buf;
        struct v4l2_plane capture_planes[MAX_PLANES];

        NvBuffer *output_buffer = NULL;
        NvBuffer *capture_buffer = NULL;

        memset(&v4l2_output_buf, 0, sizeof(v4l2_output_buf));
        memset(output_planes, 0, sizeof(output_planes));
        v4l2_output_buf.m.planes = output_planes;

        memset(&v4l2_capture_buf, 0, sizeof(v4l2_capture_buf));
        memset(capture_planes, 0, sizeof(capture_planes));
        v4l2_capture_buf.m.planes = capture_planes;

        /* Call for SetPollInterrupt.
           Refer V4L2_CID_MPEG_SET_POLL_INTERRUPT */
        ctx.dec->SetPollInterrupt();

        /* Since buffers have been queued, issue a post to start polling and
           then wait here. */
        sem_post(&ctx.pollthread_sema);
        sem_wait(&ctx.decoderthread_sema);

        /* Call for dequeuing an event.
           Refer ioctl VIDIOC_DQEVENT */
        ret = ctx.dec->dqEvent(ev, 0);
        if (ret == 0)
        {
            if (ev.type == V4L2_EVENT_RESOLUTION_CHANGE)
            {
                /* Received the resolution change event, now can do query_and_set_capture. */
                cout << "Got V4L2_EVENT_RESOLUTION_CHANGE EVENT \n";
                query_and_set_capture(&ctx);
            }
        }
        else if (ret < 0 && errno == EINVAL)
        {
            cerr << "Error in dequeueing decoder event" << endl;
            abort(&ctx);
        }

        /* dequeue from the output plane and enqueue back the buffers after reading. */
        while (1)
        {
            if ( (eos) && (ctx.dec->output_plane.getNumQueuedBuffers() == 0) )
            {
                cout << "Done processing all the buffers returning \n";
                return true;
            }

            /* dequeue a buffer for output plane. */
            if (allow_DQ)
            {
                ret = ctx.dec->output_plane.dqBuffer(v4l2_output_buf, &output_buffer, NULL, 0);
                if (ret < 0)
                {
                    if (errno == EAGAIN)
                        goto check_capture_buffers;
                    else
                    {
                        cerr << "Error DQing buffer at output plane" << endl;
                        abort(&ctx);
                        break;
                    }
                }
            }
            else
            {
                allow_DQ = true;
                memcpy(&v4l2_output_buf,&temp_buf,sizeof(v4l2_buffer));
                output_buffer = ctx.dec->output_plane.getNthBuffer(v4l2_output_buf.index);
            }

            if ((v4l2_output_buf.flags & V4L2_BUF_FLAG_ERROR) && ctx.enable_input_metadata)
            {
                v4l2_ctrl_videodec_inputbuf_metadata dec_input_metadata;

                /* Get the decoder input metadata.
                   Refer V4L2_CID_MPEG_VIDEODEC_INPUT_METADATA */
                ret = ctx.dec->getInputMetadata(v4l2_output_buf.index, dec_input_metadata);
                if (ret == 0)
                {
                    ret = report_input_metadata(&ctx, &dec_input_metadata);
                    if (ret == -1)
                    {
                        cerr << "Error with input stream header parsing" << endl;
                    }
                }
            }

            if (eos)
            {
                /* Got End Of Stream, no more queueing of buffers on OUTPUT plane. */
                goto check_capture_buffers;
            }

            if ((ctx.decoder_pixfmt == V4L2_PIX_FMT_H264) ||
                    (ctx.decoder_pixfmt == V4L2_PIX_FMT_H265) ||
                    (ctx.decoder_pixfmt == V4L2_PIX_FMT_MPEG2) ||
                    (ctx.decoder_pixfmt == V4L2_PIX_FMT_MPEG4))
            {
                if (ctx.input_nalu)
                {
                    /* read the input nal unit. */
                    read_decoder_input_nalu(ctx.in_file[current_file], output_buffer, nalu_parse_buffer,
                            CHUNK_SIZE, &ctx);
                }
                else
                {
                    /* read the input chunks. */
                    read_decoder_input_chunk(ctx.in_file[current_file], output_buffer);
                }
            }

            if (ctx.decoder_pixfmt == V4L2_PIX_FMT_MJPEG)
            {
                read_mjpeg_decoder_input(ctx.in_file[current_file], output_buffer);
            }
            if ((ctx.decoder_pixfmt == V4L2_PIX_FMT_VP9) ||
                    (ctx.decoder_pixfmt == V4L2_PIX_FMT_VP8) ||
                    (ctx.decoder_pixfmt == V4L2_PIX_FMT_AV1))
            {
                /* read the input chunks. */
                ret = read_vpx_decoder_input_chunk(&ctx, output_buffer);
                if (ret != 0)
                    cerr << "Couldn't read chunk" << endl;
            }
            v4l2_output_buf.m.planes[0].bytesused = output_buffer->planes[0].bytesused;

            if (ctx.input_nalu && ctx.copy_timestamp)
            {
                /* Update the timestamp. */
                v4l2_output_buf.flags |= V4L2_BUF_FLAG_TIMESTAMP_COPY;
                if (ctx.flag_copyts)
                    ctx.timestamp += ctx.timestampincr;
                v4l2_output_buf.timestamp.tv_sec = ctx.timestamp / (MICROSECOND_UNIT);
                v4l2_output_buf.timestamp.tv_usec = ctx.timestamp % (MICROSECOND_UNIT);
            }

            if (ctx.copy_timestamp && ctx.input_nalu && ctx.stats)
            {
              cout << "[" << v4l2_output_buf.index << "]" "dec output plane qB timestamp [" <<
                  v4l2_output_buf.timestamp.tv_sec << "s" << v4l2_output_buf.timestamp.tv_usec << "us]" << endl;
            }

            if (v4l2_output_buf.m.planes[0].bytesused == 0)
            {
                if (ctx.bQueue)
                {
                    current_file++;
                    if(current_file != ctx.file_count)
                    {
                        allow_DQ = false;
                        memcpy(&temp_buf, &v4l2_output_buf, sizeof(v4l2_buffer));
                        continue;
                    }
                }
                if(ctx.bLoop)
                {
                    current_file = current_file % ctx.file_count;
                    allow_DQ = false;
                    memcpy(&temp_buf, &v4l2_output_buf,sizeof(v4l2_buffer));
                    if (ctx.loop_count == 0 || current_loop < ctx.loop_count )
                    {
                        current_loop++;
                        continue;
                    }
                }
            }

            /* enqueue a buffer for output plane. */
            ret = ctx.dec->output_plane.qBuffer(v4l2_output_buf, NULL);
            if (ret < 0)
            {
                cerr << "Error Qing buffer at output plane" << endl;
                abort(&ctx);
                break;
            }
            if (v4l2_output_buf.m.planes[0].bytesused == 0)
            {
                eos = true;
                cout << "Input file read complete" << endl;
                goto check_capture_buffers;
            }
        }

check_capture_buffers:
        /* Dequeue from the capture plane and write them to file and enqueue back. */
        while (1)
        {
            if (!ctx.dec->capture_plane.getStreamStatus())
            {
                cout << "Capture plane not ON, skipping capture plane \n";
                break;
            }

            /* Dequeue a filled buffer. */
            ret = ctx.dec->capture_plane.dqBuffer(v4l2_capture_buf, &capture_buffer, NULL, 0);
            if (ret < 0)
            {
                if (errno == EAGAIN)
                    break;
                else
                {
                    abort(&ctx);
                    cerr << "Error while calling dequeue at capture plane" <<
                        endl;
                }
                break;
            }
            if (capture_buffer == NULL)
            {
                cout << "Got CAPTURE BUFFER NULL \n";
                break;
            }

            if (ctx.enable_metadata)
            {
                v4l2_ctrl_videodec_outputbuf_metadata dec_metadata;

                /* Get the decoder output metadata on capture-plane.
                   Refer V4L2_CID_MPEG_VIDEODEC_METADATA */
                ret = ctx.dec->getMetadata(v4l2_capture_buf.index, dec_metadata);
                if (ret == 0)
                {
                    report_metadata(&ctx, &dec_metadata);
                }
            }

            if (ctx.copy_timestamp && ctx.input_nalu && ctx.stats)
            {
              cout << "[" << v4l2_capture_buf.index << "]" "dec capture plane dqB timestamp [" <<
                  v4l2_capture_buf.timestamp.tv_sec << "s" << v4l2_capture_buf.timestamp.tv_usec << "us]" << endl;
            }

            if (!ctx.disable_rendering && ctx.stats && !ctx.vkRendering)
            {
                /* Rendering the buffer.
                   NOTE: EglRenderer requires the fd of the 0th plane to render the buffer. */
                if(ctx.capture_plane_mem_type == V4L2_MEMORY_DMABUF)
                    capture_buffer->planes[0].fd = ctx.dmabuff_fd[v4l2_capture_buf.index];

                if (ctx.eglRenderer->render(capture_buffer->planes[0].fd) == -1)
                {
                    abort(&ctx);
                    cerr << "Error while queueing buffer for rendering "
                            << endl;
                    break;
                }
            }

            /* Get the decoded buffer data dumped to file. */
            if (ctx.out_file || (!ctx.disable_rendering && !ctx.stats))
            {
                NvBufSurf::NvCommonTransformParams transform_params;
                transform_params.src_top = 0;
                transform_params.src_left = 0;
                transform_params.src_width = ctx.display_width;
                transform_params.src_height = ctx.display_height;
                transform_params.dst_top = 0;
                transform_params.dst_left = 0;
                transform_params.dst_width = ctx.display_width;
                transform_params.dst_height = ctx.display_height;
                transform_params.flag = NVBUFSURF_TRANSFORM_FILTER;
                transform_params.flip = NvBufSurfTransform_None;
                transform_params.filter = NvBufSurfTransformInter_Nearest;

                if(ctx.capture_plane_mem_type == V4L2_MEMORY_DMABUF)
                    capture_buffer->planes[0].fd = ctx.dmabuff_fd[v4l2_capture_buf.index];
                /* Perform Blocklinear to PitchLinear conversion. */
                ret = NvBufSurf::NvTransform(&transform_params, capture_buffer->planes[0].fd, ctx.dst_dma_fd);
                if (ret == -1)
                {
                    cerr << "Transform failed" << endl;
                    break;
                }
                /* Write raw video frame to file. */
                if (!ctx.stats && ctx.out_file)
                {
                    /* Dumping two planes for NV12, NV16, NV24 and three for I420 */
                    cout << "Writing to file \n";
                    dump_dmabuf(ctx.dst_dma_fd, 0, ctx.out_file);
                    dump_dmabuf(ctx.dst_dma_fd, 1, ctx.out_file);
                    if (ctx.out_pixfmt == 2)
                    {
                        dump_dmabuf(ctx.dst_dma_fd, 2, ctx.out_file);
                    }
                }

                /* Rendering the buffer. */
                if (!ctx.stats && !ctx.disable_rendering && !ctx.vkRendering)
                {
                    ctx.eglRenderer->render(ctx.dst_dma_fd);
                }

                /* Queue the buffer back once it has been used.
                   NOTE: If we are not rendering, queue the buffer back here immediately. */
                if(ctx.capture_plane_mem_type == V4L2_MEMORY_DMABUF)
                    v4l2_capture_buf.m.planes[0].m.fd = ctx.dmabuff_fd[v4l2_capture_buf.index];

                if (ctx.dec->capture_plane.qBuffer(v4l2_capture_buf, NULL) < 0)
                {
                    abort(&ctx);
                    cerr << "Error while queueing buffer at decoder capture plane"
                            << endl;
                    break;
                }
            }
        }
    }
    return eos;
}

/**
  * Decode processing function for blocking mode.
  *
  * @param ctx               : Decoder context
  * @param eos               : end of stream
  * @param current_file      : current file
  * @param current_loop      : iterator count
  * @param nalu_parse_buffer : input parsed nal unit
  */
static bool decoder_proc_blocking(context_t &ctx, bool eos, uint32_t current_file,
                                int current_loop, char *nalu_parse_buffer)
{
    int allow_DQ = true;
    int ret = 0;
    struct v4l2_buffer temp_buf;

    /* Since all the output plane buffers have been queued, we first need to
       dequeue a buffer from output plane before we can read new data into it
       and queue it again. */
    while (!eos && !ctx.got_error && !ctx.dec->isInError())
    {
        struct v4l2_buffer v4l2_buf;
        struct v4l2_plane planes[MAX_PLANES];
        NvBuffer *buffer;

        memset(&v4l2_buf, 0, sizeof(v4l2_buf));
        memset(planes, 0, sizeof(planes));

        v4l2_buf.m.planes = planes;

        /* dequeue a buffer for output plane. */
        if(allow_DQ)
        {
            ret = ctx.dec->output_plane.dqBuffer(v4l2_buf, &buffer, NULL, -1);
            if (ret < 0)
            {
                cerr << "Error DQing buffer at output plane" << endl;
                abort(&ctx);
                break;
            }
        }
        else
        {
            allow_DQ = true;
            memcpy(&v4l2_buf,&temp_buf,sizeof(v4l2_buffer));
            buffer = ctx.dec->output_plane.getNthBuffer(v4l2_buf.index);
        }

        if ((v4l2_buf.flags & V4L2_BUF_FLAG_ERROR) && ctx.enable_input_metadata)
        {
            v4l2_ctrl_videodec_inputbuf_metadata dec_input_metadata;

            /* Get the decoder input metadata.
               Refer V4L2_CID_MPEG_VIDEODEC_INPUT_METADATA */
            ret = ctx.dec->getInputMetadata(v4l2_buf.index, dec_input_metadata);
            if (ret == 0)
            {
                ret = report_input_metadata(&ctx, &dec_input_metadata);
                if (ret == -1)
                {
                  cerr << "Error with input stream header parsing" << endl;
                }
            }
        }

        if ((ctx.decoder_pixfmt == V4L2_PIX_FMT_H264) ||
                (ctx.decoder_pixfmt == V4L2_PIX_FMT_H265) ||
                (ctx.decoder_pixfmt == V4L2_PIX_FMT_MPEG2) ||
                (ctx.decoder_pixfmt == V4L2_PIX_FMT_MPEG4))
        {
            if (ctx.input_nalu)
            {
                /* read the input nal unit. */
                read_decoder_input_nalu(ctx.in_file[current_file], buffer, nalu_parse_buffer,
                        CHUNK_SIZE, &ctx);
            }
            else
            {
                /* read the input chunks. */
                read_decoder_input_chunk(ctx.in_file[current_file], buffer);
            }
        }

        if (ctx.decoder_pixfmt == V4L2_PIX_FMT_MJPEG)
        {
            read_mjpeg_decoder_input(ctx.in_file[current_file], buffer);
        }
        if ((ctx.decoder_pixfmt == V4L2_PIX_FMT_VP9) ||
                (ctx.decoder_pixfmt == V4L2_PIX_FMT_VP8) ||
                (ctx.decoder_pixfmt == V4L2_PIX_FMT_AV1))
        {
            /* read the input chunks. */
            ret = read_vpx_decoder_input_chunk(&ctx, buffer);
            if (ret != 0)
                cerr << "Couldn't read chunk" << endl;
        }
        v4l2_buf.m.planes[0].bytesused = buffer->planes[0].bytesused;

        if (ctx.input_nalu && ctx.copy_timestamp)
        {
          /* Update the timestamp. */
          v4l2_buf.flags |= V4L2_BUF_FLAG_TIMESTAMP_COPY;
          if (ctx.flag_copyts)
              ctx.timestamp += ctx.timestampincr;
          v4l2_buf.timestamp.tv_sec = ctx.timestamp / (MICROSECOND_UNIT);
          v4l2_buf.timestamp.tv_usec = ctx.timestamp % (MICROSECOND_UNIT);
        }

        if (ctx.copy_timestamp && ctx.input_nalu && ctx.stats)
        {
          cout << "[" << v4l2_buf.index << "]" "dec output plane qB timestamp [" <<
              v4l2_buf.timestamp.tv_sec << "s" << v4l2_buf.timestamp.tv_usec << "us]" << endl;
        }

        if (v4l2_buf.m.planes[0].bytesused == 0)
        {
            if (ctx.bQueue)
            {
                current_file++;
                if(current_file != ctx.file_count)
                {
                    allow_DQ = false;
                    memcpy(&temp_buf,&v4l2_buf,sizeof(v4l2_buffer));
                    continue;
                }
            }
            if(ctx.bLoop)
            {
                current_file = current_file % ctx.file_count;
                allow_DQ = false;
                memcpy(&temp_buf,&v4l2_buf,sizeof(v4l2_buffer));
            }
        }

        /* enqueue a buffer for output plane. */
        ret = ctx.dec->output_plane.qBuffer(v4l2_buf, NULL);
        if (ret < 0)
        {
            cerr << "Error Qing buffer at output plane" << endl;
            abort(&ctx);
            break;
        }
        if (v4l2_buf.m.planes[0].bytesused == 0)
        {
            eos = true;
            cout << "Input file read complete" << endl;
            break;
        }
    }
    return eos;
}

/**
  * Decode processing function.
  *
  * @param ctx  : Decoder context
  * @param argc : Argument Count
  * @param argv : Argument Vector
  */
static int
decode_proc(context_t& ctx, int argc, char *argv[])
{
    int ret = 0;
    int error = 0;
    uint32_t current_file = 0;
    uint32_t i;
    bool eos = false;
    int current_loop = 0;
    char *nalu_parse_buffer = NULL;
    NvApplicationProfiler &profiler = NvApplicationProfiler::getProfilerInstance();

    /* Set default values for decoder context members. */
    set_defaults(&ctx);

    /* Set thread name for decoder Output Plane thread. */
    pthread_setname_np(pthread_self(), "DecOutPlane");

    /* Parse application command line options. */
    if (parse_csv_args(&ctx, argc, argv))
    {
        fprintf(stderr, "Error parsing commandline arguments\n");
        return -1;
    }

    if (ctx.enable_sld && (ctx.decoder_pixfmt != V4L2_PIX_FMT_H265))
    {
        fprintf(stdout, "Slice level decoding is only applicable for H265 so disabling it\n");
        ctx.enable_sld = false;
    }

    if (ctx.enable_sld && !ctx.input_nalu)
    {
        fprintf(stdout, "Enabling input nalu mode required for slice level decode\n");
        ctx.input_nalu = true;
    }

    /* Create NvVideoDecoder object for blocking or non-blocking I/O mode. */
    if (ctx.blocking_mode)
    {
        cout << "Creating decoder in blocking mode \n";
        ctx.dec = NvVideoDecoder::createVideoDecoder("dec0");
    }
    else
    {
        cout << "Creating decoder in non-blocking mode \n";
        ctx.dec = NvVideoDecoder::createVideoDecoder("dec0", O_NONBLOCK);
    }
    TEST_ERROR(!ctx.dec, "Could not create decoder", cleanup);

    /* Open the input file. */
    ctx.in_file = (std::ifstream **)malloc(sizeof(std::ifstream *)*ctx.file_count);
    for (uint32_t i = 0 ; i < ctx.file_count ; i++)
    {
        ctx.in_file[i] = new ifstream(ctx.in_file_path[i]);
        TEST_ERROR(!ctx.in_file[i]->is_open(), "Error opening input file", cleanup);
    }

    /* Open the output file. */
    if (ctx.out_file_path)
    {
        ctx.out_file = new ofstream(ctx.out_file_path);
        TEST_ERROR(!ctx.out_file->is_open(), "Error opening output file",
                   cleanup);
    }

    /* Enable profiling for decoder if stats are requested. */
    if (ctx.stats)
    {
        profiler.start(NvApplicationProfiler::DefaultSamplingInterval);
        ctx.dec->enableProfiling();
    }

    /* Subscribe to Resolution change event.
       Refer ioctl VIDIOC_SUBSCRIBE_EVENT */
    ret = ctx.dec->subscribeEvent(V4L2_EVENT_RESOLUTION_CHANGE, 0, 0);
    TEST_ERROR(ret < 0, "Could not subscribe to V4L2_EVENT_RESOLUTION_CHANGE",
               cleanup);

    /* Set format on the output plane.
       Refer ioctl VIDIOC_S_FMT */
    ret = ctx.dec->setOutputPlaneFormat(ctx.decoder_pixfmt, CHUNK_SIZE);
    TEST_ERROR(ret < 0, "Could not set output plane format", cleanup);

    /* Configure for frame input mode for decoder.
       Refer V4L2_CID_MPEG_VIDEO_DISABLE_COMPLETE_FRAME_INPUT */
    if (ctx.input_nalu)
    {
        /* Input to the decoder will be nal units. */
        nalu_parse_buffer = new char[CHUNK_SIZE];
        printf("Setting frame input mode to 1 \n");
        ret = ctx.dec->setFrameInputMode(1);
        TEST_ERROR(ret < 0,
                "Error in decoder setFrameInputMode", cleanup);
    }
    else
    {
        /* Input to the decoder will be a chunk of bytes.
           NOTE: Set V4L2_CID_MPEG_VIDEO_DISABLE_COMPLETE_FRAME_INPUT control to
                 false so that application can send chunks of encoded data instead
                 of forming complete frames. */
        printf("Setting frame input mode to 1 \n");
        ret = ctx.dec->setFrameInputMode(1);
        TEST_ERROR(ret < 0,
                "Error in decoder setFrameInputMode", cleanup);
    }

    if (ctx.enable_sld)
    {
        printf("Setting slice mode to 1 \n");
        ret = ctx.dec->setSliceMode(1);
        TEST_ERROR(ret < 0,
                "Error in decoder setSliceMode", cleanup);
    }

    /* Disable decoder DPB management.
       NOTE: V4L2_CID_MPEG_VIDEO_DISABLE_DPB should be set after output plane
             set format */
    if (ctx.disable_dpb)
    {
        ret = ctx.dec->disableDPB();
        TEST_ERROR(ret < 0, "Error in decoder disableDPB", cleanup);
    }

    /* Enable decoder error and metadata reporting.
       Refer V4L2_CID_MPEG_VIDEO_ERROR_REPORTING */
    if (ctx.enable_metadata || ctx.enable_input_metadata)
    {
        ret = ctx.dec->enableMetadataReporting();
        TEST_ERROR(ret < 0, "Error while enabling metadata reporting", cleanup);
    }

    /* Enable max performance mode by using decoder max clock settings.
       Refer V4L2_CID_MPEG_VIDEO_MAX_PERFORMANCE */
    if (ctx.max_perf)
    {
        ret = ctx.dec->setMaxPerfMode(ctx.max_perf);
        TEST_ERROR(ret < 0, "Error while setting decoder to max perf", cleanup);
    }

    /* Set the skip frames property of the decoder.
       Refer V4L2_CID_MPEG_VIDEO_SKIP_FRAMES */
    if (ctx.skip_frames)
    {
        ret = ctx.dec->setSkipFrames(ctx.skip_frames);
        TEST_ERROR(ret < 0, "Error while setting skip frames param", cleanup);
    }

    /* Query, Export and Map the output plane buffers so can read
       encoded data into the buffers. */
    if (ctx.output_plane_mem_type == V4L2_MEMORY_MMAP) {
        /* configure decoder output plane for MMAP io-mode.
           Refer ioctl VIDIOC_REQBUFS, VIDIOC_QUERYBUF and VIDIOC_EXPBUF */
        ret = ctx.dec->output_plane.setupPlane(V4L2_MEMORY_MMAP, 2, true, false);
    } else if (ctx.output_plane_mem_type == V4L2_MEMORY_USERPTR) {
        /* configure decoder output plane for USERPTR io-mode.
           Refer ioctl VIDIOC_REQBUFS */
        ret = ctx.dec->output_plane.setupPlane(V4L2_MEMORY_USERPTR, 10, false, true);
    }
    TEST_ERROR(ret < 0, "Error while setting up output plane", cleanup);

    /* Start stream processing on decoder output-plane.
       Refer ioctl VIDIOC_STREAMON */
    ret = ctx.dec->output_plane.setStreamStatus(true);
    TEST_ERROR(ret < 0, "Error in output plane stream on", cleanup);

    /* Enable copy timestamp with start timestamp in seconds for decode fps.
       NOTE: Used to demonstrate how timestamp can be associated with an
             individual H264/H265 frame to achieve video-synchronization. */
    if (ctx.copy_timestamp && ctx.input_nalu) {
      ctx.timestamp = (ctx.start_ts * MICROSECOND_UNIT);
      ctx.timestampincr = (MICROSECOND_UNIT * 16) / ((uint32_t) (ctx.dec_fps * 16));
    }

    /* Read encoded data and enqueue all the output plane buffers.
       Exit loop in case file read is complete. */
    i = 0;
    current_loop = 1;
    while (!eos && !ctx.got_error && !ctx.dec->isInError() &&
           i < ctx.dec->output_plane.getNumBuffers())
    {
        struct v4l2_buffer v4l2_buf;
        struct v4l2_plane planes[MAX_PLANES];
        NvBuffer *buffer;

        memset(&v4l2_buf, 0, sizeof(v4l2_buf));
        memset(planes, 0, sizeof(planes));

        buffer = ctx.dec->output_plane.getNthBuffer(i);
        if ((ctx.decoder_pixfmt == V4L2_PIX_FMT_H264) ||
                (ctx.decoder_pixfmt == V4L2_PIX_FMT_H265) ||
                (ctx.decoder_pixfmt == V4L2_PIX_FMT_MPEG2) ||
                (ctx.decoder_pixfmt == V4L2_PIX_FMT_MPEG4))
        {
            if (ctx.input_nalu)
            {
                /* read the input nal unit. */
                read_decoder_input_nalu(ctx.in_file[current_file], buffer, nalu_parse_buffer,
                        CHUNK_SIZE, &ctx);
            }
            else
            {
                /* read the input chunks. */
                read_decoder_input_chunk(ctx.in_file[current_file], buffer);
            }
        }

        if (ctx.decoder_pixfmt == V4L2_PIX_FMT_MJPEG)
        {
            read_mjpeg_decoder_input(ctx.in_file[current_file], buffer);
        }
        if ((ctx.decoder_pixfmt == V4L2_PIX_FMT_VP9) ||
                (ctx.decoder_pixfmt == V4L2_PIX_FMT_VP8) ||
                (ctx.decoder_pixfmt == V4L2_PIX_FMT_AV1))
        {
            /* read the input chunks. */
            ret = read_vpx_decoder_input_chunk(&ctx, buffer);
            if (ret != 0)
                cerr << "Couldn't read chunk" << endl;
        }

        v4l2_buf.index = i;
        v4l2_buf.m.planes = planes;
        v4l2_buf.m.planes[0].bytesused = buffer->planes[0].bytesused;

        if (ctx.input_nalu && ctx.copy_timestamp)
        {
          /* Update the timestamp. */
          v4l2_buf.flags |= V4L2_BUF_FLAG_TIMESTAMP_COPY;
          if (ctx.flag_copyts)
              ctx.timestamp += ctx.timestampincr;
          v4l2_buf.timestamp.tv_sec = ctx.timestamp / (MICROSECOND_UNIT);
          v4l2_buf.timestamp.tv_usec = ctx.timestamp % (MICROSECOND_UNIT);
        }

        if (ctx.copy_timestamp && ctx.input_nalu && ctx.stats)
        {
          cout << "[" << v4l2_buf.index << "]" "dec output plane qB timestamp [" <<
              v4l2_buf.timestamp.tv_sec << "s" << v4l2_buf.timestamp.tv_usec << "us]" << endl;
        }

        if (v4l2_buf.m.planes[0].bytesused == 0)
        {
            if (ctx.bQueue)
            {
                current_file++;
                if(current_file != ctx.file_count)
                {
                    continue;
                }
            }
            if(ctx.bLoop)
            {
                current_file = current_file % ctx.file_count;
                if(ctx.loop_count == 0 || current_loop < ctx.loop_count )
                {
                    current_loop++;
                    continue;
                }
            }
        }
        /* It is necessary to queue an empty buffer to signal EOS to the decoder
           i.e. set v4l2_buf.m.planes[0].bytesused = 0 and queue the buffer. */
        ret = ctx.dec->output_plane.qBuffer(v4l2_buf, NULL);
        if (ret < 0)
        {
            cerr << "Error Qing buffer at output plane" << endl;
            abort(&ctx);
            break;
        }
        if (v4l2_buf.m.planes[0].bytesused == 0)
        {
            eos = true;
            cout << "Input file read complete" << endl;
            break;
        }
        i++;
    }


    /* Create threads for decoder output */
    if (ctx.blocking_mode)
    {
        pthread_create(&ctx.dec_capture_loop, NULL, dec_capture_loop_fcn, &ctx);
        /* Set thread name for decoder Capture Plane thread. */
        pthread_setname_np(ctx.dec_capture_loop, "DecCapPlane");
    }
    else
    {
        sem_init(&ctx.pollthread_sema, 0, 0);
        sem_init(&ctx.decoderthread_sema, 0, 0);
        pthread_create(&ctx.dec_pollthread, NULL, decoder_pollthread_fcn, &ctx);
        cout << "Created the PollThread and Decoder Thread \n";
        /* Set thread name for decoder Poll thread. */
        pthread_setname_np(ctx.dec_pollthread, "DecPollThread");
    }

    if (ctx.blocking_mode)
        eos = decoder_proc_blocking(ctx, eos, current_file, current_loop, nalu_parse_buffer);
    else
        eos = decoder_proc_nonblocking(ctx, eos, current_file, current_loop, nalu_parse_buffer);
    /* After sending EOS, all the buffers from output plane should be dequeued.
       and after that capture plane loop should be signalled to stop. */
    if (ctx.blocking_mode)
    {
        while (ctx.dec->output_plane.getNumQueuedBuffers() > 0 &&
               !ctx.got_error && !ctx.dec->isInError())
        {
            struct v4l2_buffer v4l2_buf;
            struct v4l2_plane planes[MAX_PLANES];

            memset(&v4l2_buf, 0, sizeof(v4l2_buf));
            memset(planes, 0, sizeof(planes));

            v4l2_buf.m.planes = planes;
            ret = ctx.dec->output_plane.dqBuffer(v4l2_buf, NULL, NULL, -1);
            if (ret < 0)
            {
                cerr << "Error DQing buffer at output plane" << endl;
                abort(&ctx);
                break;
            }
            if (v4l2_buf.m.planes[0].bytesused == 0)
            {
                cout << "Got EoS at output plane"<< endl;
                break;
            }

            if ((v4l2_buf.flags & V4L2_BUF_FLAG_ERROR) && ctx.enable_input_metadata)
            {
                v4l2_ctrl_videodec_inputbuf_metadata dec_input_metadata;
                /* Get the decoder input metadata.
                   Refer V4L2_CID_MPEG_VIDEODEC_INPUT_METADATA */
                ret = ctx.dec->getInputMetadata(v4l2_buf.index, dec_input_metadata);
                if (ret == 0)
                {
                    ret = report_input_metadata(&ctx, &dec_input_metadata);
                    if (ret == -1)
                    {
                      cerr << "Error with input stream header parsing" << endl;
                      abort(&ctx);
                      break;
                    }
                }
            }
        }
    }

    /* Signal EOS to the decoder capture loop. */
    ctx.got_eos = true;

cleanup:
    if (ctx.blocking_mode && ctx.dec_capture_loop)
    {
        pthread_join(ctx.dec_capture_loop, NULL);
    }
    else if (!ctx.blocking_mode)
    {
        /* Clear the poll interrupt to get the decoder's poll thread out. */
        ctx.dec->ClearPollInterrupt();
        /* If Pollthread is waiting on, signal it to exit the thread. */
        sem_post(&ctx.pollthread_sema);
        pthread_join(ctx.dec_pollthread, NULL);
    }

    if (ctx.stats && !ctx.vkRendering)
    {
        profiler.stop();
        ctx.dec->printProfilingStats(cout);
        if (ctx.eglRenderer)
        {
            ctx.eglRenderer->printProfilingStats(cout);
        }
        profiler.printProfilerData(cout);
    }

    if(ctx.capture_plane_mem_type == V4L2_MEMORY_DMABUF)
    {
        for(int index = 0 ; index < ctx.numCapBuffers ; index++)
        {
            if(ctx.dmabuff_fd[index] != 0)
            {
                ret = NvBufSurf::NvDestroy(ctx.dmabuff_fd[index]);
                if(ret < 0)
                {
                    cerr << "Failed to Destroy NvBuffer" << endl;
                }
            }
        }
    }
    if (ctx.dec && ctx.dec->isInError())
    {
        cerr << "Decoder is in error" << endl;
        error = 1;
    }

    if (ctx.got_error)
    {
        error = 1;
    }

    /* The decoder destructor does all the cleanup i.e set streamoff on output and
       capture planes, unmap buffers, tell decoder to deallocate buffer (reqbufs
       ioctl with count = 0), and finally call v4l2_close on the fd. */
    delete ctx.dec;
    /* Similarly, Renderer destructor does all the cleanup. */
    if (ctx.vkRendering)
    {
        delete ctx.vkRenderer;
    } else {
        delete ctx.eglRenderer;
    }
    for (uint32_t i = 0 ; i < ctx.file_count ; i++)
      delete ctx.in_file[i];
    delete ctx.out_file;
    if(ctx.dst_dma_fd != -1)
    {
        ret = NvBufSurf::NvDestroy(ctx.dst_dma_fd);
        ctx.dst_dma_fd = -1;
        if(ret < 0)
        {
            cerr << "Error in BufferDestroy" << endl;
            error = 1;
        }
    }
    delete[] nalu_parse_buffer;

    free (ctx.in_file);
    for (uint32_t i = 0 ; i < ctx.file_count ; i++)
      free (ctx.in_file_path[i]);
    free (ctx.in_file_path);
    free(ctx.out_file_path);
    if (!ctx.blocking_mode)
    {
        sem_destroy(&ctx.pollthread_sema);
        sem_destroy(&ctx.decoderthread_sema);
    }

    return -error;
}

/**
  * Start of video Decode application.
  *
  * @param argc : Argument Count
  * @param argv : Argument Vector
  */
int
main(int argc, char *argv[])
{


    /* create decoder context. */
    context_t ctx;
    /* default renderer is Egl */
    ctx.vkRendering = false;
    int ret = 0;
    /* save decode iterator number */
    int iterator_num = 0;

    do
    {
        /* Invoke video decode function. */
        ret = decode_proc(ctx, argc, argv);
        iterator_num++;
    } while((ctx.stress_test != iterator_num) && ret == 0);

    /* Report application run status on exit. */
    if (ret)
    {
        cout << "App run failed" << endl;
    }
    else
    {
        cout << "App run was successful" << endl;
    }

    return ret;
}
