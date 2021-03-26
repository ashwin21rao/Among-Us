#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "movable_sprite.h"
#include <vector>
#include "util.h"

class Character
{
public:
    Character(int window_width, int window_height, std::vector<std::vector<float>> colors, float speed=1.5);
    MovableSprite sprite;

    void setInitialPosition(std::pair<int, glm::vec3> cell);
    void translate(char direction, float render_time);

    bounding_box b_box;
    std::pair<int, glm::vec3> active_cell;

protected:
    std::pair<std::vector<float>, int> generateVertexData();
    void moveTo(glm::vec3 position);

private:
    std::vector<std::vector<float>> colors; // light, medium, dark
};


#endif
