#include "Display/Surface.h"

VkSurfaceKHR
Display::Surface::create(GLFWwindow* windows,
                         VkInstance& instance)
{
    VkSurfaceKHR surface;
    if (glfwCreateWindowSurface(instance,
                                windows,
                                nullptr,
                                &surface) !=
        VK_SUCCESS)
    {
        throw std::runtime_error("glfwCreateWindowSurface not success");
    }

    return surface;
}

VkSurfaceFormatKHR
Display::Surface::chooseFormat(const std::vector<VkSurfaceFormatKHR>
                               &availableFormats)
{
    for (const auto& availableFormat : availableFormats)
    {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
            availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        {
            return availableFormat;
        }
    }
    return availableFormats[0]; //else
}

VkPresentModeKHR
Display::Surface::choosePresentMode(const std::vector<VkPresentModeKHR>
    & availablePresentModes)
{
    for (const auto& availablePresentMode : availablePresentModes)
    {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            return availablePresentMode;
        }
    }
    return VK_PRESENT_MODE_FIFO_KHR;
}


VkExtent2D
Display::Surface::chooseExtent(GLFWwindow* window,
    const VkSurfaceCapabilitiesKHR& capabilities)
{
    if (capabilities.currentExtent.width != UINT32_MAX)
    {
        return capabilities.currentExtent;
    }
    else
    {
        int width = 0,
            height = 0;
        glfwGetFramebufferSize(window, &width, &height);
        VkExtent2D actualExtent = {};
        actualExtent.width = static_cast<uint32_t>(width);
        actualExtent.height = static_cast<uint32_t>(height);

        /*For max and min functions need include <algorithm> header*/

        actualExtent.width =
            std::max(capabilities.minImageExtent.width,
                std::min(capabilities.maxImageExtent.width,
                    actualExtent.width));
        actualExtent.height =
            std::max(capabilities.minImageExtent.height,
                std::min(capabilities.maxImageExtent.height,
                    actualExtent.height));
        return actualExtent;
    }
}

Display::Surface::SupportDetails
Display::Surface::querySupportDetails(const VkPhysicalDevice& device,
    const VkSurfaceKHR& surface)
{
    SupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device,
        surface,
        &details.capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(device,
        surface,
        &formatCount,
        nullptr);
    if (formatCount != 0u)
    {
        details.formats.resize(static_cast<size_t>(formatCount));
        vkGetPhysicalDeviceSurfaceFormatsKHR(device,
            surface,
            &formatCount,
            details.formats.data());
    }

    uint32_t presentModesCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(device,
        surface,
        &presentModesCount,
        nullptr);
    if (presentModesCount != 0u)
    {
        details.presentModes.resize(static_cast<size_t>(presentModesCount));
        vkGetPhysicalDeviceSurfacePresentModesKHR(device,
            surface,
            &presentModesCount,
            details.presentModes.data()
        );
    }

    return details;
}
