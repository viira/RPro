#ifndef DEVICE_LOGICAL_H
#define DEVICE_LOGICAL_H

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "Device/config.h"
#include "Device/Queues.h"
#include "ValidationLayers.h"

namespace Device::Logical
{
    /*

    */
    VkDevice create(const VkPhysicalDevice &physicalDevice,
                    const VkSurfaceKHR &surface,
                    const Device::Queues::FamilyIndices &familyIndices);
};

#endif