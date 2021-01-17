#include "window/window.h"

Window::Window()
{
    window = nullptr;
}

Window::~Window()
{

}

void
Window::init()
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    window = glfwCreateWindow(weight, height,
                              "WindowsTitle",
                              nullptr, nullptr);
}

void
Window::shut()
{
    glfwDestroyWindow(window);

    glfwTerminate();
}

GLFWwindow*
Window::self()
{
    return window;
}