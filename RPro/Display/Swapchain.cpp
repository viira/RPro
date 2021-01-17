#include "Display/Swapchain.h"

VkSwapchainKHR
Display::Swapchain::create(GLFWwindow* window,
                           const VkDevice &device,
                           const VkSurfaceKHR &surface,
                           const Display::Surface::SupportDetails
                           &surfaceSupportDetails,
                           const Device::Queues::FamilyIndices
                           &queueFamilyIndices,
                           Display::Swapchain::Details
                           &swapchainDetails)
{
    VkSurfaceFormatKHR surfaceFormat = 
    Display::Surface::chooseFormat(surfaceSupportDetails.formats);

    VkPresentModeKHR presentMode =
    Display::Surface::choosePresentMode(surfaceSupportDetails.presentModes);

    swapchainDetails.extent =
    Display::Surface::chooseExtent(window, surfaceSupportDetails.capabilities);
    swapchainDetails.imageFormat = surfaceFormat.format;

    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface;
    createInfo.presentMode = presentMode;
    createInfo.imageFormat = swapchainDetails.imageFormat;
    createInfo.imageExtent = swapchainDetails.extent;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageArrayLayers = 1u; // This is always 1 unless that 
                                      // application is a stereoscopic 3D
                                      // application.
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    uint32_t imageCount =
    surfaceSupportDetails.capabilities.minImageCount + 1u;
    // 0 is a special value that means that there is no maximum
    if (surfaceSupportDetails.capabilities.maxImageCount > 0u &&
        imageCount > surfaceSupportDetails.capabilities.maxImageCount)
    {
        imageCount = surfaceSupportDetails.capabilities.maxImageCount;
    }

    createInfo.minImageCount = imageCount;


    if (queueFamilyIndices.graphic !=
        queueFamilyIndices.present)
    {
        uint32_t indices[] = {
            queueFamilyIndices.graphic.value(), // 1
            queueFamilyIndices.present.value()  // 2
        };
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2u;
        createInfo.pQueueFamilyIndices = indices;
    }
    else
    {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0; // optional
        createInfo.pQueueFamilyIndices = nullptr; // optional
    }

    // Transform images in the swap chain like a 90 degree clockwise rotation
    // or horizontal flip
    // To use no transforms, set the current transform
    createInfo.preTransform =
    surfaceSupportDetails.capabilities.currentTransform;

    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;

    VkSwapchainKHR swapchain;

    if (vkCreateSwapchainKHR(device,
                             &createInfo,
                             nullptr,
                             &swapchain) !=
        VK_SUCCESS)
    {
        throw std::runtime_error("createSwapChain not success");
    }

    return swapchain;
}

std::vector<VkImage>
Display::Swapchain::retrieveImages(const VkDevice &device,
                                   const VkSwapchainKHR &swapchain)
{
    uint32_t imageCount = 0u;
    vkGetSwapchainImagesKHR(device,
                            swapchain,
                            &imageCount,
                            nullptr);
    std::vector<VkImage> images(imageCount);
    vkGetSwapchainImagesKHR(device,
                            swapchain,
                            &imageCount,
                            images.data());
    return images;
}

/*
VkExtent2D&
Swapchain::getExtent()
{
    return extent;
}*/