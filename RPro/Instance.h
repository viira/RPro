#ifndef INSTANCE_H
#define INSTANCE_H

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <stdexcept>

#include "ValidationLayers.h"

namespace Instance
{
    VkInstance create();
}

#endif