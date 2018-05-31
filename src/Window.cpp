#include "Window.h"
#include "Timer.h"
#include "GlobalDefs.h"
#include "Input.h"
#include "Application.h"

#include <iostream>


GLFWwindow* Window::_window;
Application Window::_application;
uintl16 Window::_w;
uintl16 Window::_h;


void Window::create(const uintl16& w, const uintl16& h, const char* title, const bool& fullscreen)
{
#if PERFORMANCE_TESTS
    GlobalTimer::_name = "Window creation";
    GlobalTimer::start();
#endif
    _w = w;
    _h = h;

    if(!glfwInit())     std::cerr << "Failed to init GLFW!\n";

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DECORATED, !fullscreen);
    //glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    _window = glfwCreateWindow(w, h, title, nullptr, nullptr);

    if(!_window)        std::cerr << "Failed to create Window!\n";

    glViewport(0, 0, w, h);

    glfwMakeContextCurrent(_window);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if(err != GLEW_OK)  std::cerr << "Failed to init GLEW!\n";
#if PERFORMANCE_TESTS
    GlobalTimer::stop();
#endif
    glfwSwapInterval(1);

    _application.update_dimensions(w, h);
    _application.init();
    Input::init(_window);

    glfwSetWindowSizeCallback(_window, resize_callback);
}


void Window::update()
{
    glClearColor(0.2f, 0.5f, 0.8f, 1.0f);

    while(!glfwWindowShouldClose(_window))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT);

        _application.process();

        /*
        glBegin(GL_TRIANGLES);
        glVertex2f(0.5f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glVertex2f(-0.5f, -0.5f);
        glEnd();
        */


        //BasicRenderer::draw_rect({0, 0}, {0, 0}, {0, 0}, {0, 0, 0, 0});

        glfwSwapBuffers(_window);
    }
}


void Window::destroy()
{
    glfwDestroyWindow(_window);
}


void Window::resize_callback(GLFWwindow* window, int w, int h)
{
    _w = w;
    _h = h;
    _application.update_dimensions(_w, _h);
    glViewport(0, 0, _w, _h);
}
