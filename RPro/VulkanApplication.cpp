#include "VulkanApplication.h"

VulkanApplication::VulkanApplication()
{

}

VulkanApplication::~VulkanApplication()
{

}

void
VulkanApplication::init(GLFWwindow* window)
{
    instance = Instance::create();

    surface = Display::Surface::create(window, instance);

    Device::Queues::FamilyIndices queueFamilyIndices = {};
    Display::Surface::SupportDetails surfaceSupportDetails = {};

    physicalDevice = Device::Physical::pick(instance, surface,
                                            queueFamilyIndices,
                                            surfaceSupportDetails);

    device = Device::Logical::create(physicalDevice, surface,
                                     queueFamilyIndices);

    queueHandles = Device::Queues::retrieveHandles(device,
                                                   queueFamilyIndices);
    
    Display::Swapchain::Details swapchainDetails = {};

    swapchain = Display::Swapchain::create(window, device, surface,
                                           surfaceSupportDetails,
                                           queueFamilyIndices,
                                           swapchainDetails);

    swapchainImages = Display::Swapchain::retrieveImages(device, swapchain);

    displayImageViews = Display::Image::Views::create(device,
                                                      swapchainDetails,
                                                      swapchainImages);

    renderPass = Graphic::Render::Pass::create(device, swapchainDetails);

    graphicsPipeline = Graphic::Pipeline::create(device, swapchainDetails,
                                                 renderPass, pipelineLayout);

    framebuffers = Buffers::Frame::create(device, displayImageViews,
                                          renderPass, swapchainDetails);

    commandPool = Buffers::Command::Pool::create(device, queueFamilyIndices);

    commandBuffers = Buffers::Command::create(device, framebuffers,
                                              commandPool, renderPass,
                                              swapchainDetails,
                                              graphicsPipeline);

    imageAvailableSemaphore = Semaphores::create(device);
    renderFinishedSemaphore = Semaphores::create(device);
    
}

void
VulkanApplication::shut()
{
    vkDestroySemaphore(device, imageAvailableSemaphore, nullptr);
    vkDestroySemaphore(device, renderFinishedSemaphore, nullptr);
    vkDestroyCommandPool(device, commandPool, nullptr);
    for (auto &framebuffer : framebuffers)
    {
        vkDestroyFramebuffer(device, framebuffer, nullptr);
    }
    vkDestroyPipeline(device, graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
    vkDestroyRenderPass(device, renderPass, nullptr);
    for (VkImageView &imageView : displayImageViews)
    {
        vkDestroyImageView(device, imageView, nullptr);
    }
    vkDestroySwapchainKHR(device, swapchain, nullptr);
    vkDestroyDevice(device, nullptr);
    vkDestroySurfaceKHR(instance, surface, nullptr);
    vkDestroyInstance(instance, nullptr);
}

void
VulkanApplication::draw()
{
    Frame::draw(device, swapchain, imageAvailableSemaphore, renderFinishedSemaphore,
                commandBuffers, queueHandles);
}

void
VulkanApplication::deviceWaitIdle()
{
    vkDeviceWaitIdle(device);
}