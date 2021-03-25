#ifndef _SHAPE_H
#define _SHAPE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shape
{
public:
    Shape(int window_width, int window_height);
    void createShape(float *vertices, int size, int number_of_vertices, float scaling_factor=1);
    void translate(int key, float render_time);
    void rotate(glm::vec3 axis, float render_time);
    void render() const;
    void setViewMatrix(glm::mat4 new_view_matrix);
    glm::vec3 getCenter() const;
    glm::mat4 model_matrix, view_matrix, projection_matrix, transformation_matrix;
    glm::mat4 translation_matrix, rotation_matrix, scaling_matrix;
    glm::mat4 camera_rotation_matrix;
    glm::vec3 rotation_axis = glm::vec3(0.5, 1.0, 0.0);

private:
    void calculateMatrices();
    float x_speed, y_speed, z_speed, rotation_speed;
    unsigned int vao;
    int num_vertices;
};


#endif
