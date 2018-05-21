#include "Input.h"

#include <stdexcept>
#include <iostream>


std::unique_ptr<uintl8> Input::_keys {new uintl8[128]};


void Input::init(GLFWwindow* window)
{
    glfwSetKeyCallback(window, key_callback);
}


void Input::process()
{
}


void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)  glfwSetWindowShouldClose(window, true);
    else
    {
        if(action == GLFW_PRESS)        _keys.get()[key] = true;
        else if(action == GLFW_RELEASE) _keys.get()[key] = false;
    }
}