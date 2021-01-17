#ifndef GRAPHIC_RENDER_H
#define GRAPHIC_RENDER_H

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "Display/Swapchain.h"

namespace Graphic::Render::Pass
{
    VkRenderPass create(VkDevice &device,
                        Display::Swapchain::Details &swapchainDetails);
};

#endif