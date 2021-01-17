#ifndef DISPLAY_SWAPCHAIN_H
#define DISPLAY_SWAPCHAIN_H

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <vector>
#include <cstdint>

#include "Display/Surface.h"
#include "Device/Queues.h"

namespace Display::Swapchain
{
    struct Details
    {
        VkFormat imageFormat;
        VkExtent2D extent;
    };

    VkSwapchainKHR create(GLFWwindow* window,
                          const VkDevice &device,
                          const VkSurfaceKHR &surface,
                          const Display::Surface::SupportDetails
                          &surfaceSupportDetails,
                          const Device::Queues::FamilyIndices
                          &queueFamilyIndices,
                          Display::Swapchain::Details
                          &swapchainDetails);

    std::vector<VkImage> retrieveImages(const VkDevice& device,
                                        const VkSwapchainKHR& swapchain);
};

#endif