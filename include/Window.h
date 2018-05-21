#pragma once

#include "IntTypes.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
private:
    static GLFWwindow* _window;

public:
    static void create(const uintl16& w, const uintl16& h, const char* title, const bool& fullscreen);
    static void update();
    static void destroy();
};

