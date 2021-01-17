#ifndef IMAGE_VIEWS_H
#define IMAGE_VIEWS_H

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <vector>
#include <stdexcept>

#include "Display/Swapchain.h"

namespace Display::Image::Views
{
    std::vector<VkImageView>
    create(const VkDevice &device,
           const Display::Swapchain::Details &swapchainDetails,
           const std::vector<VkImage> &swapchainImages);
};

#endif