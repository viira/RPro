#ifndef VALIDATION_LAYERS_H
#define VALIDATION_LAYERS_H

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <vector>

namespace ValidationLayers
{
    bool checkSupport();
    const bool requested = true;
    //const bool requested = false;
    const std::vector<const char*> names =
    {
        "VK_LAYER_KHRONOS_validation"
    };
}

#endif