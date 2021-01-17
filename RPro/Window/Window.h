#ifndef __WINDOW_H__ 
#define __WINDOW_H__ 

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

class Window
{
public:
    Window();
    ~Window();
    void init();
    void shut();
    GLFWwindow* self();
private:
    GLFWwindow* window;
    uint32_t height = 500u;
    uint32_t weight = 500u;
};

#endif