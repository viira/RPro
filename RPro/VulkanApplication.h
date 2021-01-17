#ifndef VULKAN_APPLICATION_H
#define VULKAN_APPLICATION_H

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <optional>

#include "Window/Window.h"
#include "ValidationLayers.h"
#include "Instance.h"
#include "Device/Physical.h"
#include "Device/Logical.h"
#include "Device/Queues.h"
#include "Display/Surface.h"
#include "Display/Swapchain.h"
#include "Display/ImageViews.h"
#include "Graphic/Render.h"
#include "Graphic/Pipeline.h"
#include "Buffers/Frame.h"
#include "Buffers/Command.h"
#include "Semaphores.h"
#include "Frame.h"

class VulkanApplication
{
public:
    VulkanApplication();
    ~VulkanApplication();
    void init(GLFWwindow* window);
    void shut();
    void draw();
    void deviceWaitIdle();
private:
    VkInstance instance = VK_NULL_HANDLE;
    VkSurfaceKHR surface = VK_NULL_HANDLE;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device = VK_NULL_HANDLE;
    Device::Queues::Handles queueHandles = {};
    VkSwapchainKHR swapchain = VK_NULL_HANDLE;
    std::vector<VkImage> swapchainImages;
    std::vector<VkImageView> displayImageViews;
    VkRenderPass renderPass = VK_NULL_HANDLE;
    VkPipelineLayout pipelineLayout = VK_NULL_HANDLE;
    VkPipeline graphicsPipeline = VK_NULL_HANDLE;
    std::vector<VkFramebuffer> framebuffers;
    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;
    VkSemaphore imageAvailableSemaphore;
    VkSemaphore renderFinishedSemaphore;
};

#endif