#include "Device/Queues.h"

Device::Queues::FamilyIndices
Device::Queues::findFamilies(const VkPhysicalDevice &device,
                             const VkSurfaceKHR &surface)
{
    FamilyIndices indices;

    uint32_t queueFamilyCount = 0u;
    vkGetPhysicalDeviceQueueFamilyProperties(device,
                                             &queueFamilyCount,
                                             nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device,
                                             &queueFamilyCount,
                                             queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily: queueFamilies)
    {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            indices.graphic = i;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device,
                                             i,
                                             surface, 
                                             &presentSupport);

        if (presentSupport)
        {
            indices.present = i;
        }

        if (indices.isComplite())
        {
            break;
        }

        ++i;
    }

    return indices;
}

std::vector<VkDeviceQueueCreateInfo>
Device::Queues::fillCreateInfos(const VkPhysicalDevice &device,
                                const VkSurfaceKHR &surface,
                                const FamilyIndices &familyIndices)
{
    //auto familyIndices = findFamilies(device, surface);

    std::set<uint32_t> uniqueQueueFamilies = 
    {
        familyIndices.graphic.value(),
        familyIndices.present.value()
    };

    std::vector<VkDeviceQueueCreateInfo> createInfos;

    for (uint32_t queueFamily : uniqueQueueFamilies)
    {
        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        float queuePriorities = 1.0f;
        queueCreateInfo.queueCount = 1u;
        queueCreateInfo.pQueuePriorities = &queuePriorities;

        createInfos.push_back(queueCreateInfo);
    }

    return createInfos;
}

Device::Queues::Handles
Device::Queues::retrieveHandles(const VkDevice &device,
                                const FamilyIndices &familyIndices)
{
    Handles handles = {};
    vkGetDeviceQueue(device,
                     familyIndices.graphic.value(),
                     0,
                     &handles.graphic);
    vkGetDeviceQueue(device,
                     familyIndices.present.value(),
                     0,
                     &handles.present);
    return handles;
}