#ifndef _SHADER_H_
#define _SHADER_H_

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    Shader(const char *vertex_shader_path, const char *fragment_shader_path);
    void use() const;
    void transform(glm::mat4 transformation_matrix, const char *matrix_name) const;
    void setColor(glm::vec3 color, const char *color_name) const;
    unsigned int shader_id;

private:
    const char *vertex_shader_source, *fragment_shader_source;

    static void checkErrors(const std::string &error_type, unsigned int id);
    unsigned int compileVertexShader();
    unsigned int compileFragmentShader();
};

#endif
