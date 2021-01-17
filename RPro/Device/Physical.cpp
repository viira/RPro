#include "Device/Physical.h"

VkPhysicalDevice
Device::Physical::pick(const VkInstance &instance,
                       const VkSurfaceKHR &surface,
                       Device::Queues::FamilyIndices &familyIndices,
                       Display::Surface::SupportDetails
                       &surfaceSupportDetails)
{
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    Device::Queues::FamilyIndices currentFamilyIndices = {};
    Display::Surface::SupportDetails currentSurfaseSupportDetails = {};
    uint32_t deviceCount = 0u;

    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    if (deviceCount == 0u)
    {
        throw std::runtime_error("Failed to find physical device with " \
                                 "Vulkan support!");
    }
    std::vector<VkPhysicalDevice> physicalDevices(
        static_cast<size_t>(deviceCount)
    );
    vkEnumeratePhysicalDevices(instance,
                               &deviceCount,
                               physicalDevices.data());
    std::optional<int> maxScore; // Controversial decision
    for (auto& device: physicalDevices)
    {
        if (isSuitable(device, surface,
                       currentFamilyIndices,
                       currentSurfaseSupportDetails))
        {
            int score = rateSuitability(device);
            if (score > maxScore)
            {
                maxScore = score;
                physicalDevice = device;
                familyIndices = currentFamilyIndices;
                surfaceSupportDetails = currentSurfaseSupportDetails;
            }
        }
    }

    if (physicalDevice == VK_NULL_HANDLE)
    {
        throw std::runtime_error("Failed to find a suitable physical " \
                                 "device!");
    }
    return physicalDevice;
}

bool
Device::Physical::isSuitable(const VkPhysicalDevice &device,
                             const VkSurfaceKHR &surface,
                             Queues::FamilyIndices &familyIndices,
                             Display::Surface::SupportDetails
                             &surfaceSupportDetails)
{
    familyIndices = Queues::findFamilies(device, surface);

    bool extensionsSupported = checkExtensionSupport(device);

    bool surfaceAdequate = false;
    if (extensionsSupported)
    {
        surfaceSupportDetails =
        Display::Surface::querySupportDetails(device,
                                              surface);
        surfaceAdequate = !surfaceSupportDetails.formats.empty() &&
                          !surfaceSupportDetails.presentModes.empty();
    }

    return familyIndices.isComplite() && // indices.isComplite()
           extensionsSupported &&
           surfaceAdequate;
}


int
Device::Physical::rateSuitability(const VkPhysicalDevice &device)
{
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);

    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    int score = 0;

    // Discrete GPUs have a significant performance advantage
    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
    {
        score += 1000;
    }

    // Maximum possible size of textures affects graphics quality
    score += deviceProperties.limits.maxImageDimension2D;

    // Application can't function without geometry shaders
    if (!deviceFeatures.geometryShader)
    {
        return 0;
    }

    return score;
}

bool
Device::Physical::checkExtensionSupport(const VkPhysicalDevice &device)
{
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device,
                                         nullptr,
                                         &extensionCount,
                                         nullptr);
    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device,
                                         nullptr,
                                         &extensionCount,
                                         availableExtensions.data());
    std::set<std::string> requiredExtensions(
        Device::Config::Physical::deviceExtensions.begin(),
        Device::Config::Physical::deviceExtensions.end());

    for (const auto& extension: availableExtensions)
    {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}