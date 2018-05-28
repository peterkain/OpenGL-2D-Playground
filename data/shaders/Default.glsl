#shadertype vertex
#version 330 core

layout (location = 0) in vec2 _pos;

uniform mat4 u_mvp;

void main(void)
{
    gl_Position = u_mvp * vec4(_pos.x, _pos.y, 0.0, 1.0);
}

#shadertype fragment
#version 330 core

uniform vec4 u_color;

out vec4 o_color;

void main(void)
{
    o_color = u_color;
}
