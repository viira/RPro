#ifndef GRAPHIC_SHADERS_H
#define GRAPHIC_SHADERS_H

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <vector>
#include <fstream>
#include <cstring>

namespace Graphic::Shaders
{
    std::vector<char> readFile(const std::string filename);
    VkShaderModule createModule(const VkDevice &device,
                                const std::vector<char> &code);
};

#endif