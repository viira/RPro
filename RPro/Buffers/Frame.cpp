#include "Buffers/Frame.h"

std::vector<VkFramebuffer>
Buffers::Frame::create(const VkDevice &device,
                       const std::vector<VkImageView> &displayImageViews,
                       const VkRenderPass &renderPass,
                       const Display::Swapchain::Details &swapchainDetails)
{
    std::vector<VkFramebuffer> framebuffers(displayImageViews.size());
    for (size_t i = 0; i < displayImageViews.size(); ++i)
    {
        VkImageView attachments[] = 
        {
            displayImageViews[i]
        };
        VkFramebufferCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        createInfo.renderPass = renderPass;
        createInfo.width = swapchainDetails.extent.width;
        createInfo.height = swapchainDetails.extent.height;
        createInfo.pAttachments = attachments;
        createInfo.attachmentCount = 1u;
        createInfo.layers = 1u;

        if (vkCreateFramebuffer(device, &createInfo, nullptr,
                                &framebuffers[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("vkCreateFramebuffer not success");
        }
    }
    return framebuffers;
}