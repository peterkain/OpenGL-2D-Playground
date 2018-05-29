#include "Input.h"

#include <stdexcept>
#include <iostream>


std::unique_ptr<uintl8> Input::_keys {new uintl8[128]};
bool Input::_wireframe {false};
Camera Input::_camera;


void Input::init(GLFWwindow* window)
{
    glfwSetKeyCallback(window, key_callback);
}


void Input::process()
{
    if(_keys.get()[GLFW_KEY_D])
        _camera.move_right();
    if(_keys.get()[GLFW_KEY_A])
        _camera.move_left();
}


void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)  glfwSetWindowShouldClose(window, true);
    if(key == GLFW_KEY_F1 && action == GLFW_PRESS)
    {
        if((_wireframe = !_wireframe))    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else
    {
        if(action == GLFW_PRESS)        _keys.get()[key] = true;
        else if(action == GLFW_RELEASE) _keys.get()[key] = false;
    }
}
