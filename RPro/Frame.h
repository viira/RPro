#ifndef FRAME_H
#define FRAME_H

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "Device/Queues.h"

#include <vector>

namespace Frame
{
    void draw(VkDevice& device, VkSwapchainKHR& swapchain,
              VkSemaphore& imageAvailableSemaphore,
              VkSemaphore& renderFinishedSemaphore,
              std::vector<VkCommandBuffer>& commandBuffers,
              Device::Queues::Handles& queueHandles);
}

#endif