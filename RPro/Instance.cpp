#include "Instance.h"

VkInstance
Instance::create()
{
    if (ValidationLayers::requested &&
        !ValidationLayers::checkSupport())
    {
        throw std::runtime_error("Validation layers requested, " \
            "but not available!");
    } //not need runtime

    VkApplicationInfo applicationInfo = {};
    applicationInfo.apiVersion = VK_API_VERSION_1_0; //!!!
    applicationInfo.applicationVersion = VK_MAKE_VERSION(1u, 0u, 0u);
    applicationInfo.engineVersion = VK_MAKE_VERSION(1u, 0u, 0u);
    applicationInfo.pApplicationName = "ApplicationForDrawGraphics";
    applicationInfo.pEngineName = "No Engine";
    //applicationInfo.pNext = nullptr;
    applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;

    VkInstanceCreateInfo createInfo = {};

    /*
    auto requiredExtensions = getRequiredExtensions();

    createInfo.ppEnabledExtensionNames = requiredExtensions.data();
    createInfo.enabledExtensionCount =
        static_cast<uint32_t>(requiredExtensions.size());

    */ //VK_ERROR_EXTENSION_NOT_PRESENT on my PC. Return here later

    /*
    for (auto& extName : requiredExtensions)
    {
        std::cout << extName << std::endl;
    }
    */

    // Temporary solution:
    createInfo.ppEnabledExtensionNames =
        glfwGetRequiredInstanceExtensions(&createInfo.enabledExtensionCount);
    //

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
    createInfo.pApplicationInfo = &applicationInfo;
    //createInfo.pNext = nullptr;
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

    //std::cout << vkCreateInstance(&createInfo, nullptr, &instance) << std::endl;

    VkInstance instance;

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
    {
        throw std::runtime_error("vkCreateInstance not success");
    }

    return instance;
}