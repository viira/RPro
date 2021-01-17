# CMakeList.txt : CMake project for Rina, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

include_directories (${CMAKE_CURRENT_SOURCE_DIR})

# Add source to this project's executable.
add_executable (RPro
                "RPro.h"
                "RPro.cpp"
                "Window/Window.h"
                "Window/Window.cpp"
                "VulkanApplication.h"
                "VulkanApplication.cpp"
                "Application.h"
                "Application.cpp"
                "ValidationLayers.h"
                "ValidationLayers.cpp"
                "Instance.h"
                "Instance.cpp"
                "Display/Surface.h"
                "Display/Surface.cpp"
                "Device/Queues.h"
                "Device/Queues.cpp"
                "Device/Physical.h"
                "Device/Physical.cpp"
                "Display/Swapchain.h"
                "Display/Swapchain.cpp"
                "Device/config.h"
                "Device/Logical.h"
                "Device/Logical.cpp"
                "Display/ImageViews.h"
                "Display/ImageViews.cpp"
                "Graphic/Shaders.h"
                "Graphic/Shaders.cpp"
                "Graphic/Pipeline.h"
                "Graphic/Pipeline.cpp"
                "Graphic/Render.h"
                "Graphic/Render.cpp"
                "Buffers/Frame.h"
                "Buffers/Frame.cpp"
                "Buffers/Command.h"
                "Buffers/Command.cpp"
                "Semaphores.h"
                "Semaphores.cpp"
                "Frame.h"
                "Frame.cpp")

target_link_libraries (RPro glfw ${GLFW_LIBRARIES} Vulkan::Vulkan)

# TODO: Add tests and install targets if needed.
