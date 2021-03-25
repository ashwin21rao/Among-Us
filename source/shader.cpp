#include "shader.h"
#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char *vertex_shader_path, const char *fragment_shader_path)
{
    shader_id = glCreateProgram();

    std::ifstream vertex_shader_file(vertex_shader_path);
    std::ifstream fragment_shader_file(fragment_shader_path);

    std::stringstream vertex_shader_stream, fragment_shader_stream;
    vertex_shader_stream << vertex_shader_file.rdbuf();
    fragment_shader_stream << fragment_shader_file.rdbuf();

    std::string vertex_shader_string = vertex_shader_stream.str();
    std::string fragment_shader_string = fragment_shader_stream.str();
    vertex_shader_source = vertex_shader_string.c_str();
    fragment_shader_source = fragment_shader_string.c_str();

    unsigned int vertex_shader = compileVertexShader();
    unsigned int fragment_shader = compileFragmentShader();

    glAttachShader(shader_id, vertex_shader);
    glAttachShader(shader_id, fragment_shader);
    glLinkProgram(shader_id);
    checkErrors("SHADER_PROGRAM", shader_id);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

unsigned int Shader::compileVertexShader()
{
    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertex_shader);
    checkErrors("VERTEX", vertex_shader);

    return vertex_shader;
}

unsigned int Shader::compileFragmentShader()
{
    unsigned int fragment_shader;
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragment_shader);
    checkErrors("FRAGMENT", fragment_shader);

    return fragment_shader;
}

void Shader::checkErrors(const std::string &error_type, unsigned int id)
{
    int success;
    char error_log[512];

    if (error_type == "SHADER_PROGRAM")
    {
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(id, 512, nullptr, error_log);
            fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n", error_log);
        }
    }
    else
    {
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(id, 512, nullptr, error_log);
            if (error_type == "VERTEX")
                fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n", error_log);
            else if (error_type == "FRAGMENT")
                fprintf(stderr, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", error_log);
        }
    }
}

void Shader::use() const
{
    glUseProgram(shader_id);
}

void Shader::transform(glm::mat4 transformation_matrix, const char *matrix_name) const
{
    glUniformMatrix4fv(glGetUniformLocation(shader_id, matrix_name), 1, GL_FALSE, glm::value_ptr(transformation_matrix));
}
