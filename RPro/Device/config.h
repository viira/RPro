#ifndef DEVICE_CONFIG_H
#define DEVICE_CONFIG_H

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <vector>

namespace Device::Config::Physical
{
    const std::vector<const char*> deviceExtensions = 
    {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
}

#endif