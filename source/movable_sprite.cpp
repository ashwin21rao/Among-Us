#include "movable_sprite.h"

MovableSprite::MovableSprite(int window_width, int window_height, float speed)
        : Sprite(window_width, window_height), speed(speed)
{

}

void MovableSprite::translate(int key, float render_time)
{
    glm::vec3 translation_vector(0.0f);

    if (key == 'l')
        translation_vector = glm::vec3(speed*render_time, 0.0, 0.0);
    else if (key == 'j')
        translation_vector = glm::vec3(-speed*render_time, 0.0, 0.0);
    else if (key == 'i')
        translation_vector = glm::vec3(0.0, speed*render_time, 0.0);
    else if (key == 'k')
        translation_vector = glm::vec3(0.0, -speed*render_time, 0.0);

    translation_matrix = glm::translate(translation_matrix, translation_vector);
    calculateMatrices();
}
