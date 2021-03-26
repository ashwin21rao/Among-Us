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

    void moveTo(glm::vec3 position);

    float width, height;
    bounding_box b_box;

protected:
    std::pair<std::vector<float>, int> generateVertexData();

private:
    std::vector<std::vector<float>> colors; // light, medium, dark
};


#endif
