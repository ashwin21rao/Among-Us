#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
out vec4 vertex_color;
uniform mat4 trans_matrix;

void main()
{
    gl_Position = trans_matrix * vec4(pos, 1.0);
    vertex_color = vec4(color, 1.0);
}