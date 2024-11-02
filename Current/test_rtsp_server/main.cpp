#include <stdio.h>
#include "opencv2/opencv.hpp"
#include <string>

//For receiving the RTSP video stream with FFplay, execute: "ffplay -rtsp_flags listen -i rtsp://localhost:8554/stream" before exectuing this program.
int main()
{
    // 10000 frames, resolution 640x480, and 10 fps
    int width = 640;
    int height = 480;
    int n_frames = 100000;
    int fps = 30;

    const std::string output_stream = "rtsp://192.168.1.37:8554/stream";   //Send RTSP to port 8554 of "localhost", with stream named "stream".

    //Open FFmpeg application as sub-process.
    //FFmpeg input PIPE : RAW images in BGR color format.
    //FFmpeg output: RTSP stream encoded with H.264 codec (using libx264 encoder).
    //Adding '-re' slows down the transmission to rate of the fps (for simulating a "virtual webcam").
    std::string ffmpeg_cmd =
        std::string("ffmpeg -re -f rawvideo -r ") +
        std::to_string(fps) +
        " -video_size " + std::to_string(width) +
        "x" + std::to_string(height) +
        " -pixel_format bgr24 -i pipe: -vcodec libx264 -crf 24 -pix_fmt yuv420p -f rtsp " +
        output_stream;

    //Execute FFmpeg as sub-process, open stdin pipe (of FFmpeg sub-process) for writing.

    //https://batchloaf.wordpress.com/2017/02/12/a-simple-way-to-read-and-write-audio-and-video-files-in-c-using-ffmpeg-part-2-video/
    FILE* pipeout = popen(ffmpeg_cmd.c_str(), "w");     //Linux (assume ffmpeg exist in /usr/bin/ffmpeg (and in path).

    cv::Mat frame = cv::Mat(height, width, CV_8UC3); //Initialize frame.

    for (int i = 0; i < n_frames; i++)
    {
        //Build synthetic image for testing ("render" a video frame):
        frame = cv::Scalar(60, 60, 60); //Fill background with dark gray
        cv::putText(frame, std::to_string(i+1), cv::Point(width/2 - 100*(int)(std::to_string(i+1).length()), height/2+100), cv::FONT_HERSHEY_DUPLEX, 10, cv::Scalar(255, 30, 30), 20);  // Draw a blue number
        cv::imshow("frame", frame); //Show the frame for testing
        cv::waitKey(1);

        //Write width*height*3 bytes to stdin pipe of FFmpeg sub-process (assume frame data is continuous in the RAM).
        fwrite(frame.data, 1, (size_t)width*height*3, pipeout);
    }

    pclose(pipeout);    //Linux

    return 0;
}
