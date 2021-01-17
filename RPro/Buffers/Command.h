#ifndef BUFFERS_COMMAND_H
#define BUFFERS_COMMAND_H

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <stdexcept>

#include "Device/Queues.h"
#include "Display/Swapchain.h"

namespace Buffers::Command
{
    std::vector<VkCommandBuffer>
    create(VkDevice &device,
           std::vector<VkFramebuffer> &framebuffer,
           VkCommandPool &commandPool,
           VkRenderPass &renderPass,
           Display::Swapchain::Details &swapchainDetails,
           VkPipeline &graphicsPipeline);

    namespace Pool
    {
        VkCommandPool
        create(VkDevice &device,
               Device::Queues::FamilyIndices &queueFamilyIndices);
    }
}

#endif