#ifndef DEVICE_PHYSICAL_H
#define DEVICE_PHYSICAL_H

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <iostream>
#include <vector>
#include <optional>
#include <map>
#include <set>

#include "Device/Queues.h"
#include "Device/config.h"
#include "Display/Swapchain.h"

namespace Device::Physical
{
    /*
        The point of this PhysicalDevice is to evaluate a more suitable GPU 
        and use it. Multiple devices cannot be used in this manager at the
        same time. But it is possible
    */
    VkPhysicalDevice pick(const VkInstance &instance,
                          const VkSurfaceKHR &surface,
                          Device::Queues::FamilyIndices &familyIndices,
                          Display::Surface::SupportDetails
                          &surfaceSupportDetails);
    bool isSuitable(const VkPhysicalDevice &device,
                    const VkSurfaceKHR &surface,
                    Device::Queues::FamilyIndices &familyIndices,
                    Display::Surface::SupportDetails
                    &surfaceSupportDetails);
    int rateSuitability(const VkPhysicalDevice &device);
    bool checkExtensionSupport(const VkPhysicalDevice &device);

}

#endif