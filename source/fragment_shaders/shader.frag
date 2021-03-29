#version 330 core

in vec3 vertex_color;
out vec4 FragColor;

void main()
{
    float ambient = 1.0;
    FragColor = vec4(ambient * vertex_color, 1.0);
}