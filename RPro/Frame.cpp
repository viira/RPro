#include "Frame.h"

void
Frame::draw(VkDevice &device, VkSwapchainKHR &swapchain,
            VkSemaphore &imageAvailableSemaphore,
            VkSemaphore & renderFinishedSemaphore,
            std::vector<VkCommandBuffer> &commandBuffers,
            Device::Queues::Handles &queueHandles)
{
    /*Function will perform the following operations:
      -  Acquire an image from the swap chain
      -  Execute the command buffer with that image as attachment in the
      framebuffer
      -  Return the image to the swap chain for presentation
    */
    uint32_t imageIndex;
    vkAcquireNextImageKHR(device, swapchain, UINT64_MAX /*Disable timeout*/,
                          imageAvailableSemaphore, VK_NULL_HANDLE,
                          &imageIndex);
    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.pCommandBuffers = &commandBuffers[imageIndex];
    submitInfo.commandBufferCount = 1u;
    VkSemaphore waitSemaphores[] = 
    {
        imageAvailableSemaphore
    };
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.waitSemaphoreCount = 1u;
    VkPipelineStageFlags waitStages[] = 
    {
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
    };
    submitInfo.pWaitDstStageMask = waitStages;
    // pWaitSemaphores and pWaitDstStageMask have the same index as they are 
    // referenced. I.e we wait with writing colors to the image until it's
    // available.
    VkSemaphore signalSemaphores [] = 
    {
        renderFinishedSemaphore
    };
    submitInfo.pSignalSemaphores = signalSemaphores;
    submitInfo.signalSemaphoreCount = 1u;

    // submit the command buffer to the graphics queue

    if (vkQueueSubmit(queueHandles.graphic, 1, &submitInfo, VK_NULL_HANDLE) !=
        VK_SUCCESS)
    {
        throw std::runtime_error("vkQueueSubmit not success");
    }

    VkPresentInfoKHR presentInfo = {};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.pWaitSemaphores = signalSemaphores;
    presentInfo.waitSemaphoreCount = 1u;
    VkSwapchainKHR swapchains[] = 
    {
        swapchain
    };
    presentInfo.pSwapchains = swapchains;
    presentInfo.swapchainCount = 1u;
    presentInfo.pImageIndices = &imageIndex;
    presentInfo.pResults = nullptr;

    vkQueuePresentKHR(queueHandles.present, &presentInfo); //Yoy!

}