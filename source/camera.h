#ifndef _CAMERA_H
#define _CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

class Camera
{
public:
    explicit Camera(glm::vec3 target, float zoom);
    void translate(int key, float render_time);
    void moveAndFocus(glm::vec3 new_target);
    glm::mat4 getViewMatrix();
    std::vector<glm::vec3> getAxes();
    glm::vec3 getPosition();

private:
    float speed, zoom;
    glm::vec3 position, target;
    glm::vec3 x_axis, y_axis, z_axis, world_up;
    glm::mat4 view_matrix;
    void focus(glm::vec3 new_target);
    void calculateAxes();
    void calculateViewMatrix();
};


#endif
