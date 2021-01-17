#ifndef DISPLAY_SURFACE_H
#define DISPLAY_SURFACE_H

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <stdexcept>
#include <vector>

namespace Display::Surface
{
    struct SupportDetails
    {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    VkSurfaceKHR create(GLFWwindow* windows,
                        VkInstance &instance);

    VkSurfaceFormatKHR chooseFormat(const std::vector<VkSurfaceFormatKHR> 
                                    &availableFormats);

    VkPresentModeKHR choosePresentMode(const std::vector<VkPresentModeKHR>&
                                       availablePresentModes);

    VkExtent2D chooseExtent(GLFWwindow* window,
                            const VkSurfaceCapabilitiesKHR& capabilities);

    SupportDetails querySupportDetails(const VkPhysicalDevice& device,
                                       const VkSurfaceKHR& surface);
};

#endif