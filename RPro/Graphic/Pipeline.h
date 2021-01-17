#ifndef GRAPHIC_PIPELINE_H
#define GRAPHIC_PIPELINE_H

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <stdexcept>

#include "Graphic/Shaders.h"
#include "Display/Swapchain.h"

namespace Graphic::Pipeline
{
    VkPipeline create(const VkDevice& device,
                      const Display::Swapchain::Details &swapchainDetails,
                      const VkRenderPass &renderPass,
                      VkPipelineLayout &pipelineLayout);
};

#endif