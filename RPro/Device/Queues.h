#ifndef DEVICE_QUEUES_H
#define DEVICE_QUEUES_H

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <optional>
#include <vector>
#include <set>
#include <iostream>

namespace Device::Queues
{
    struct FamilyIndices
    {
        std::optional<uint32_t> graphic;
        std::optional<uint32_t> present;

        bool isComplite()
        {
            return graphic.has_value() &&
                present.has_value();
        }
    };

    struct Handles
    {
                          // We can add logic to explicitly prefer a
                          // physical device that supports drawing and
                          // presentation in the same queue for improved
        VkQueue graphic;  // performance.
        VkQueue present;  // But throughout the program we will treat 
                          // them as if they were separate queues for a 
                          // uniform approach.

    };

    FamilyIndices findFamilies(const VkPhysicalDevice &device,
                               const VkSurfaceKHR &surface);

    std::vector<VkDeviceQueueCreateInfo>
    fillCreateInfos(const VkPhysicalDevice &device,
                    const VkSurfaceKHR &surface,
                    const FamilyIndices &familyInices);

    Handles retrieveHandles(const VkDevice& device,
                            const FamilyIndices& familyIndices);
    
};

#endif