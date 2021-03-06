#include "Graphic/Render.h"

VkRenderPass
Graphic::Render::Pass::create(VkDevice &device,
                              Display::Swapchain::Details &swapchainDetails)
{
    VkAttachmentDescription colorAttachment = {};
    colorAttachment.format = swapchainDetails.imageFormat;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    
    VkAttachmentReference colorAttachmentRef = {};
    colorAttachmentRef.attachment = 0u;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpassDescription = {};
    subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpassDescription.colorAttachmentCount = 1u;
    subpassDescription.pColorAttachments = &colorAttachmentRef;

    VkSubpassDependency subpassDependency = {};
    subpassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    subpassDependency.dstSubpass = 0u;
    subpassDependency.srcStageMask =
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpassDependency.srcAccessMask = 0;
    subpassDependency.dstStageMask = 
        VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpassDependency.dstAccessMask = 
        VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    createInfo.attachmentCount = 1u;
    createInfo.pAttachments = &colorAttachment;
    createInfo.subpassCount = 1u;
    createInfo.pSubpasses = &subpassDescription;
    createInfo.dependencyCount = 1u;
    createInfo.pDependencies = &subpassDependency;

    VkRenderPass renderPass;

    if (vkCreateRenderPass(device, &createInfo, nullptr, &renderPass) !=
        VK_SUCCESS)
    {
        throw std::runtime_error("vkCreateRenderPass not success");
    }
    return renderPass;
}