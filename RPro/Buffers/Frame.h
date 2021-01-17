#ifndef BUFFERS_FRAME_H
#define BUFFERS_FRAME_H

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "Display/Swapchain.h"

#include <vector>

namespace Buffers::Frame
{
    std::vector<VkFramebuffer>
    create(const VkDevice &device,
           const std::vector<VkImageView> &displayImageViews,
           const VkRenderPass &renderPass,
           const Display::Swapchain::Details &swapchainDetails);
};

#endif