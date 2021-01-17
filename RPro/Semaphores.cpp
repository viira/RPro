#include "Semaphores.h"

VkSemaphore
Semaphores::create(VkDevice &device)
{
    VkSemaphoreCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkSemaphore semaphore;

    if (vkCreateSemaphore(device, &createInfo, nullptr, &semaphore) !=
        VK_SUCCESS)
    {
        throw std::runtime_error("vkCreateSemaphore not success");
    }
    return semaphore;
}