#include "movable_sprite.h"

MovableSprite::MovableSprite(int window_width, int window_height, float speed)
        : Sprite(window_width, window_height), speed(speed)
{

}

void MovableSprite::translate(char direction, float render_time)
{
    glm::vec3 translation_vector(0.0f);

    if (direction == 'r')
        translation_vector = glm::vec3(speed*render_time, 0.0, 0.0);
    else if (direction == 'l')
        translation_vector = glm::vec3(-speed*render_time, 0.0, 0.0);
    else if (direction == 'u')
        translation_vector = glm::vec3(0.0, speed*render_time, 0.0);
    else if (direction == 'd')
        translation_vector = glm::vec3(0.0, -speed*render_time, 0.0);

    translation_matrix = glm::translate(translation_matrix, translation_vector);
    calculateMatrices();
}
