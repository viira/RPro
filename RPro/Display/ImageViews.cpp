#include "ImageViews.h"

std::vector<VkImageView>
Display::Image::Views::create(const VkDevice &device,
                              const Display::Swapchain::Details &swapchainDetails,
                              const std::vector<VkImage> &swapchainImages)
{
    std::vector<VkImageView> imageViews(swapchainImages.size());
    for (size_t i = 0; i < swapchainImages.size(); ++i)
    {
        VkImageViewCreateInfo createInfo = {};

        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.format = swapchainDetails.imageFormat;
        createInfo.image = swapchainImages[i];
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;

        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.layerCount = 1;
        createInfo.subresourceRange.levelCount = 1;

        if (vkCreateImageView(device,
                              &createInfo,
                              nullptr,
                              &imageViews[i]) != VK_SUCCESS)
        {
            throw std::runtime_error("vkCreateImageView not success");
        }
    }
    return imageViews;
}