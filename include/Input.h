#ifndef PG_Input_H
#define PG_Input_H

#pragma once

#include "types/IntTypes.h"
#include "Camera.h"

#include <GLFW/glfw3.h>
#include <memory>

class Input
{
public:
    Input() = delete;

    static void init(GLFWwindow* window);
    static void process();

    static uintl8* keys();

    static Camera camera;

private:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

private:
    static bool _wireframe;
    static std::unique_ptr<uintl8> _keys;
};

#endif
