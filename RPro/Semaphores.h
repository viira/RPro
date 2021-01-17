#ifndef SEMAPHORES_H
#define SEMAPHORES_H

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <stdexcept>

namespace Semaphores
{
    VkSemaphore create(VkDevice &device);
};

#endif