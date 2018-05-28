#pragma once

#include "types/IntTypes.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Application;

class Window
{
private:
    static GLFWwindow* _window;
    static Application _application;
    static uintl16 _w, _h;

private:
    static void resize_callback(GLFWwindow* window, int w, int h);

public:
    static void create(const uintl16& w, const uintl16& h, const char* title, const bool& fullscreen);
    static void update();
    static void destroy();
};

