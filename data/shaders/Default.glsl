#shadertype vertex
#version 330 core

layout (location = 0) in vec2 _pos;

void main(void)
{
    gl_Position = vec4(_pos.x, _pos.y, 0.0, 1.0);
}

#shadertype fragment
#version 330 core

out vec4 o_color;

void main(void)
{
    o_color = vec4(1, 0, 1, 1);
}