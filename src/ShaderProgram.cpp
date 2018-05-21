#include "ShaderProgram.h"
#include "ErrorCodes.h"

#include <iostream>
#include <vector>


void check_for_errors(const GLuint& id, const char& type);


ShaderProgram::ShaderProgram()
{
    _program = glCreateProgram();
}



void ShaderProgram::create(const ShaderSource& shader)
{
    std::vector<GLuint> shader_ids;
    shader_ids.resize(shader.sources.size());
    for(uintf8 i{0}; i < shader.sources.size();)
    {
        GLenum shader_enum = (i == ShaderFile::VERTEX ? GL_VERTEX_SHADER :
                              i == ShaderFile::FRAGMENT ? GL_FRAGMENT_SHADER :
                              -1);
        shader_ids[i] = glCreateShader(shader_enum);

        const GLchar* source[1] = { shader.sources.at(i).c_str() };
        glShaderSource(shader_ids[i], 1, source, nullptr);

        glCompileShader(shader_ids[i]);
        check_for_errors(shader_ids[i], 's');

        glAttachShader(_program, shader_ids[i]);
        ++i;
    }

    for(auto& e : shader_ids)   glDeleteShader(e);

    glLinkProgram(_program);
    check_for_errors(_program, 'p');
}



void check_for_errors(const GLuint& id, const char& type)
{
    GLint success;
    GLint log_length;
    (type == 'p') ? glGetProgramiv(id, GL_LINK_STATUS, &success)
                  : glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        (type == 'p') ? glGetProgramiv(id, GL_INFO_LOG_LENGTH, &log_length)
                      : glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_length);

        std::vector<GLchar> info_log (log_length);
        (type == 'p') ? glGetProgramInfoLog (id, log_length, &log_length, &info_log[0]) 
                      : glGetShaderInfoLog  (id, log_length, &log_length, &info_log[0]);

        std::cout << std::string { info_log.begin(), info_log.end() } << "\n";

        glDeleteShader(id);
        std::exit(COMPILE_LINK_ERROR);
    }
}
