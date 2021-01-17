#include "application.h"

Application::Application()
{

}

Application::~Application()
{

}

void
Application::launch()
{
    window.init();
    vulkanApplication.init(window.self());
    mainLoop();
    cleanup();
}

void
Application::mainLoop() 
{
    while (!glfwWindowShouldClose(window.self()))
    {
        glfwPollEvents();
        vulkanApplication.draw();
    }

    vulkanApplication.deviceWaitIdle();
}

void
Application::cleanup() 
{
    vulkanApplication.shut();
    window.shut();

}

std::vector<const char*>
Application::getRequiredExtensions()
{
    uint32_t glfwExtensionCount = 0u;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> requiredExtensions(glfwExtensions,
                                                glfwExtensions +
                                                glfwExtensionCount);
    if (ValidationLayers::requested)
    {
        requiredExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        //VK_ERROR_EXTENSION_NOT_PRESENT on my PC. Return here later
    }

    return requiredExtensions;
}
