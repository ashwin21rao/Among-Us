#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

Camera::Camera(glm::vec3 target, float zoom) : speed(1.5), zoom(zoom), world_up(glm::vec3(0.0, 1.0, 0.0))
{
    moveAndFocus(target);
}

void Camera::translate(int key, float render_time)
{
    float new_speed = render_time * speed;
    if(key == 'd')
        position += new_speed * x_axis, target += new_speed * x_axis;
    else if(key == 'a')
        position -= new_speed * x_axis, target -= new_speed * x_axis;
    else if(key == 'w')
        position += new_speed * y_axis, target += new_speed * y_axis;
    else if(key == 's')
        position -= new_speed * y_axis, target -= new_speed * y_axis;
    else if(key == 'q')
        position += new_speed * z_axis, target += new_speed * z_axis;
    else if(key == 'e')
        position -= new_speed * z_axis, target -= new_speed * z_axis;

    calculateViewMatrix();
}

void Camera::focus(glm::vec3 new_target)
{
    target = new_target;
    calculateAxes();
    calculateViewMatrix();
}

void Camera::moveAndFocus(glm::vec3 new_target)
{
    position = glm::vec3(new_target.x, new_target.y, zoom);
    focus(new_target);
}

void Camera::calculateViewMatrix()
{
    view_matrix = glm::lookAt(position, target, world_up);
}

void Camera::calculateAxes()
{
    z_axis = glm::normalize(position - target);
    x_axis = glm::normalize(glm::cross(world_up, z_axis));
    y_axis = glm::normalize(glm::cross(z_axis, x_axis));
}

glm::mat4 Camera::getViewMatrix()
{
    return view_matrix;
}

std::vector<glm::vec3> Camera::getAxes()
{
    return std::vector<glm::vec3>({x_axis, y_axis, z_axis});
}

glm::vec3 Camera::getPosition()
{
    return position;
}
