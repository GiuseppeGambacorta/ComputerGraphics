#include "Callbacks.h"
#include <iostream>

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    std::cout << "Mouse Position - x: " << xpos << ", y: " << ypos << std::endl;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    static double xpos, ypos;
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        glfwGetCursorPos(window, &xpos, &ypos);
        std::cout << "Mouse left button pressed at - x: " << xpos << ", y: " << ypos << std::endl;
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    switch (key) {
    case GLFW_KEY_A:
        if (action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        break;

    default:
        break;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    std::cout << "Window resized - width: " << width << ", height: " << height << std::endl;
}
