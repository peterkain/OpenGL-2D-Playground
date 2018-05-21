#include "Application.h"
#include "ShaderProgram.h"
#include "BasicRenderer.h"


std::unordered_map<std::string, GLuint> Application::_programs;


void Application::init()
{
    BasicRenderer::init();

    ShaderProgram sp_default;

    sp_default.create(ShaderFile::parse_shader("data/shaders/Default.glsl"));

    _programs["default"] = sp_default.id();
}


void Application::render()
{
    BasicRenderer::draw_rect(_programs["default"], {0, 0}, {0, 0}, {0, 0}, {0, 0, 0, 1});
}


void Application::quit()
{
    for(auto& e : _programs)    glDeleteProgram(e.second);
}