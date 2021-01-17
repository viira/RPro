#include "Buffers/Command.h"

VkCommandPool
Buffers::Command::Pool::create(VkDevice &device,
                               Device::Queues::FamilyIndices
                               &queueFamilyIndices)
{
    VkCommandPoolCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    createInfo.queueFamilyIndex = queueFamilyIndices.graphic.value();
    createInfo.flags = 0;

    VkCommandPool commandPool;

    if (vkCreateCommandPool(device, &createInfo, nullptr, &commandPool) !=
        VK_SUCCESS)
    {
        throw std::runtime_error("vkCreateCommandPool not success");
    }

    return commandPool;
}

std::vector<VkCommandBuffer>
Buffers::Command::create(VkDevice &device,
                         std::vector<VkFramebuffer> &framebuffers,
                         VkCommandPool &commandPool,
                         VkRenderPass &renderPass,
                         Display::Swapchain::Details &swapchainDetails,
                         VkPipeline &graphicsPipeline)
{
    std::vector<VkCommandBuffer> commandBuffers(framebuffers.size());
    VkCommandBufferAllocateInfo allocateInfo = {};
    allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocateInfo.commandPool = commandPool;
    allocateInfo.commandBufferCount = (uint32_t) commandBuffers.size();
    allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

    if (vkAllocateCommandBuffers(device, &allocateInfo,
                                 commandBuffers.data()) != VK_SUCCESS)
    {
        throw std::runtime_error("vkAllocateCommandBuffers not success");
    }

    // recording command buffers
    for (size_t i = 0; i < commandBuffers.size(); ++i)
    {
        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = 0;
        beginInfo.pInheritanceInfo = nullptr;

        if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS)
        {
            throw std::runtime_error("vkBeginCommandBuffer not success");
        }

        VkRenderPassBeginInfo renderPassBeginInfo = {};
        renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassBeginInfo.renderPass = renderPass;
        renderPassBeginInfo.framebuffer = framebuffers[i];
        renderPassBeginInfo.renderArea.extent = swapchainDetails.extent;
        VkOffset2D renderAreaOffset = {};
        renderAreaOffset.x = 0;
        renderAreaOffset.y = 0;
        renderPassBeginInfo.renderArea.offset = renderAreaOffset;
        VkClearValue clearValue = {};
        VkClearColorValue clearColorValue = {};
        clearColorValue = {0.0f, 0.0f, 0.0f, 1.0f}; //Black with 100% opacity
        clearValue.color = clearColorValue;
        renderPassBeginInfo.pClearValues = &clearValue;
        renderPassBeginInfo.clearValueCount = 1u;
        /*This is related with VK_ATTACHMENT_LOAD_OP_CLEAR. Clear color
        to simply be black with 100% opacity.*/
        
        vkCmdBeginRenderPass(commandBuffers[i], &renderPassBeginInfo,
                             VK_SUBPASS_CONTENTS_INLINE); // Start a drawing
        
        vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS,
                          graphicsPipeline);

        vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);

        vkCmdEndRenderPass(commandBuffers[i]);

        if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("vkEndCommandBuffer not success");
        }

    }

    return commandBuffers;
}