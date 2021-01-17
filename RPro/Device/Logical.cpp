#include "Device/Logical.h"

VkDevice
Device::Logical::create(const VkPhysicalDevice &physicalDevice,
                        const VkSurfaceKHR &surface,
                        const Device::Queues::FamilyIndices &familyIndices)
{
    auto deviceQueueCreateInfos = 
    Device::Queues::fillCreateInfos(physicalDevice, surface, familyIndices);
    VkPhysicalDeviceFeatures features = {};

    //auto deviceQueueCreateInfos = queues.getCreateInfos();

    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = deviceQueueCreateInfos.data();
    createInfo.queueCreateInfoCount = 
        static_cast<uint32_t>(deviceQueueCreateInfos.size());
    createInfo.pEnabledFeatures = &features;
    
    createInfo.enabledExtensionCount = 
        static_cast<uint32_t>(Device::Config::Physical::deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = 
        Device::Config::Physical::deviceExtensions.data();

    /*************************************************************************
    Warning! It is for to be compatible with older implementations.
    That means that the enabledLayerCount and ppEnabledLayerNames fields of 
    VkDeviceCreateInfo are ignored by up-to-date implementations of Vulkan.
    *************************************************************************/

    if (ValidationLayers::requested)
    {
        createInfo.enabledLayerCount =
            static_cast<uint32_t>(ValidationLayers::names.size());
        createInfo.ppEnabledLayerNames = 
            ValidationLayers::names.data();
    }
    else
    {
        createInfo.enabledLayerCount = 0u;
    }

    /************************************************************************/

    VkDevice logicalDevice;

    if (vkCreateDevice(physicalDevice,
                       &createInfo,
                       nullptr,
                       &logicalDevice) != VK_SUCCESS)
    {
        throw std::runtime_error("vkCreateDevice not success");
    }
    return logicalDevice;
}
