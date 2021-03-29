#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 color;

out vec3 FragPos;
out vec3 Normal;
out vec3 vertex_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));

    vec3 aNormal = vec3(0.0, 0.0, 1.0);
    Normal = mat3(transpose(inverse(model))) * aNormal;

    vertex_color = color;
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
