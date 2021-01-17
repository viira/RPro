#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>

#include <cstdlib>
#include <vector>
#include <cstring>
#include <cassert>

#include "Window/Window.h"
#include "VulkanApplication.h"
#include "ValidationLayers.h"
#include "Buffers/Frame.h"

class Application
{
public:
    Application();
    ~Application();
    void launch();
private:
    void mainLoop();
    void cleanup();

    //Objects
    Window window = Window();
    VulkanApplication vulkanApplication = VulkanApplication();

    std::vector<const char*> getRequiredExtensions();

    // Finally work with Debugger, write Debugger template policy. Or no?
};

#endif