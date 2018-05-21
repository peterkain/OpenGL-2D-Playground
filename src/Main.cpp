#include "Window.h"
#include "IntTypes.h"
#include "GlobalDefs.h"
#include "Timer.h"

#include <iostream>


constexpr uintl16 WIDTH     {800};
constexpr uintl16 HEIGHT    {600};
constexpr char TITLE []     {"OpenGL 2D Playground"};
constexpr bool FULLSCREEN   {false};


struct OnExit { ~OnExit() { std::cin.get(); glfwTerminate(); } } __playground_oe__;


int main()
{
#if PERFORMANCE_TESTS
    Timer t {"Program"};
#endif
    Window::create(WIDTH, HEIGHT, TITLE, FULLSCREEN);
    Window::update();
    Window::destroy();
}