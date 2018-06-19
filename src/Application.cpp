#include "Application.h"
#include "ShaderProgram.h"
#include "BasicRenderer.h"

#include "math/Convert.h"

#include <GLFW/glfw3.h>
#include <iostream>


Application::Application()
{
}


void Application::update_dimensions(const uintl16& w, const uintl16& h)
{
    _w = w;
    _h = h;
    BasicRenderer::update_proj(_w, _h);
}


void Application::init_shaders()
{
    ShaderProgram sp_default;

    sp_default.create(ShaderFile::parse_shader("data/shaders/Default.glsl"));

    _programs["default"] = sp_default.id();
}


void Application::load_levels()
{
    _levels[0].set_level("data/levels/DebugFeatureTest.lvl");
    _curr_lvl = _levels.size() - 1;
}


void Application::init()
{
    BasicRenderer::init();
    init_shaders();
    load_levels();
}


void Application::process()
{
    //BasicRenderer::draw_rect(_programs["default"], {64.0f, 64.0f}, 0, {0, 0}, {16, 16}, {1, 0.7, 0, 1});
    _levels[_curr_lvl].render(_programs["default"]);
    _levels[_curr_lvl].process_entities(_programs["default"]);
}


void Application::quit()
{
    for(auto& e : _programs)    glDeleteProgram(e.second);
}
