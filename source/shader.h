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
    void setMat4(glm::mat4 matrix, const char *var_name) const;
    void setVec3(glm::vec3 vec, const char *var_name) const;
    void setFloat(float val, const char *var_name) const;
    unsigned int shader_id;

private:
    const char *vertex_shader_source, *fragment_shader_source;

    static void checkErrors(const std::string &error_type, unsigned int id);
    unsigned int compileVertexShader();
    unsigned int compileFragmentShader();
};

#endif
