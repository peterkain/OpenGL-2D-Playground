#include "Application.h"
#include "ShaderProgram.h"
#include "BasicRenderer.h"

#include "math/Convert.h"

#include <GLFW/glfw3.h>


Application::Application()
{
}


void Application::init_shaders()
{
    ShaderProgram sp_default;

    sp_default.create(ShaderFile::parse_shader("data/shaders/Default.glsl"));

    _programs["default"] = sp_default.id();
}


void Application::load_levels()
{
    _levels[0] = {"data/levels/test.lvl"};
    _curr_lvl = _levels.size() - 1;
}


void Application::init()
{
    BasicRenderer::init();
    init_shaders();
    load_levels();
}


void Application::render()
{
    // Next up: Implementing SpriteBatching
    for(intf8 j {0}; j < 33; ++j)
        for(intf8 i {0}; i < 59; ++i)
            BasicRenderer::draw_rect(_programs["default"], {i * 16.0f + 16.0f, j * 16.0f + 16.0f}, glfwGetTime() * 2, {0, 1}, {16, 16}, {1, 0.5, 0, 1});
}


void Application::quit()
{
    for(auto& e : _programs)    glDeleteProgram(e.second);
}