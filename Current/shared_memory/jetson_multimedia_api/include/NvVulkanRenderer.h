/*
 * Copyright (c) 2023, NVIDIA CORPORATION. All rights reserved.
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

/**
 * @file
 * <b>NVIDIA Multimedia API: Vulkan Renderer API</b>
 *
 * @b Description: This file declares the NvVulkan Renderer API.
 */
#ifndef __NV_VULKAN_RENDERER_H__
#define __NV_VULKAN_RENDERER_H__

#include <vector>
#include <limits>
#include <algorithm>

#define VK_USE_PLATFORM_XLIB_KHR
#include <vulkan/vulkan.h>
#include "NvElement.h"

#include <X11/Xlib.h>
#include <vulkan/vulkan_xlib.h>
#include <X11/Xutil.h>
/**
 * @defgroup l4t_mm_nvvulkanrenderer_group Rendering API
 *
 * The \c %NvVulkanRenderer API uses external dma_buf extension to
 * import the foreign FD and then display it using Vulkan swapchain.
 *
 * @ingroup aa_framework_api_group
 * @{
 */

/**
 *
 * @c %NvVulkanRenderer is a helper class for rendering using Vulkan
 * The renderer requires the file descriptor (FD) of a buffer
 * as an input. The rendering rate, in frames per second (fps), is
 * configurable.
 *
 * The renderer creates an X Window of its own. The width, height,
 * horizontal offset, and vertical offset of the window are
 * configurable.
 */

struct MemoryTypeResult {
    bool found;
    uint32_t typeIndex;
};

struct QueueFamilyIndices {
    int graphicsFamily = -1;
    int computeFamily = -1;
    int presentFamily = -1;
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

class NvVulkanRenderer:public NvElement
{
private:
    Display * m_XDisplay;    /**< Connection to the X server created using
                                  XOpenDisplay(). */
    Window m_XWindow;        /**< Holds the window to be used for rendering created using
                                  XCreateWindow(). */


    VkInstance m_instance;
    VkDebugUtilsMessengerEXT m_debugMessenger;
    QueueFamilyIndices m_queueFamilyIndices;
    VkPhysicalDevice m_physicalDevice;
    VkDevice m_device;
    VkQueue m_graphicsQueue;
    VkQueue m_presentQueue;
    VkSurfaceKHR m_surface;

    VkSwapchainKHR m_swapChain;
    std::vector<VkImage> m_swapChainImages;
    VkFormat m_swapChainImageFormat;
    VkExtent2D m_swapChainExtent;

    std::vector<VkDeviceMemory> m_vkImageMemory;
    int m_vkImageMemoryIndex, m_oldImageIndex;
    VkCommandPool m_commandPool;
    VkCommandBuffer m_commandBuffer;

    VkSemaphore m_imageAvailableSemaphore;
    VkSemaphore m_renderFinishedSemaphore;
    VkFence m_inFlightFence;

    const std::vector<const char*> m_validationLayers = {
#ifdef USE_VALIDATION
    "VK_LAYER_KHRONOS_validation",
#endif
    };

    const std::vector<const char*> m_instanceExtensions{
#ifdef USE_VALIDATION
        VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
#endif
        VK_KHR_SURFACE_EXTENSION_NAME,
        VK_KHR_XLIB_SURFACE_EXTENSION_NAME,
    };

    const std::vector<const char*> m_deviceExtensions{
        VK_KHR_EXTERNAL_MEMORY_EXTENSION_NAME,
        VK_KHR_EXTERNAL_MEMORY_FD_EXTENSION_NAME,
        VK_EXT_EXTERNAL_MEMORY_DMA_BUF_EXTENSION_NAME,
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    };

    template <typename T>
    uint32_t ui32Size(const T& container)
    {
        return static_cast<uint32_t>(container.size());
    }
    VkImageTiling m_imageTiling = VK_IMAGE_TILING_OPTIMAL;
    VkFormat m_imageFormat = VK_FORMAT_R8G8B8A8_UNORM;

   /**
     * Constructor called by the wrapper creatVulkanRenderer.
     */
    NvVulkanRenderer(const char *name, uint32_t width, uint32_t height,
                  uint32_t x_offset, uint32_t y_offset);

    static const NvElementProfiler::ProfilerField valid_fields =
            NvElementProfiler::PROFILER_FIELD_TOTAL_UNITS |
            NvElementProfiler::PROFILER_FIELD_FPS |
            NvElementProfiler::PROFILER_FIELD_LATE_UNITS;

public:
    /**
     * Creates a new Vulkan-based renderer named @a name.
     *
     * This method creates a new X window for rendering, of size @a
     * width and @a height, that is offset by @a x_offset and @a
     * y_offset. If @a width or @a height is zero, a full screen
     * window is created with @a x_offset and @a y_offset set to zero.
     *
     * @param[in] name Specifies a pointer to a unique name to identity the
     *                 element instance.
     * @param[in] width Specifies the width of the window in pixels.
     * @param[in] height Specifies the height of the window in pixels.
     * @param[in] x_offset Specifies the horizontal offset of the window in pixels.
     * @param[in] y_offset Specifies the vertical offset of the window in pixels.
     * @return A reference to the newly created renderer object, otherwise @c NULL in
     *          case of failure during initialization.
     */
     static NvVulkanRenderer *createVulkanRenderer(const char *name, uint32_t width,
                                          uint32_t height, uint32_t x_offset,
                                          uint32_t y_offset);
     ~NvVulkanRenderer();

    void initVulkan();
    void createInstance();
    void createSurface();
    void getPhysicalDevice();
    void getQueueFamilies();
    void createDevice();
    void createSwapChain();
    void createCommandPool();
    void createCommandBuffer();
    void createSyncObjects();
    void displayFrame(VkImage image);
    void recordCommandBuffer(VkImage image, uint32_t imageIndex);
    void createVkImageFromFd(int fd);
    void render(int fd);
    void setSize(uint32_t width, uint32_t height);
    PFN_vkVoidFunction getInstanceFunction(VkInstance instance, const char* name);

    uint32_t m_windowWidth;
    uint32_t m_windowHeight;
};
/** @} */
#endif
