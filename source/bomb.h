#ifndef _BOMB_H
#define _BOMB_H

#include "sprite.h"
#include "util.h"

class Bomb
{
public:
    Bomb(int window_width, int window_height);
    Sprite sprite;

    void moveTo(glm::vec3 position);

    bounding_box b_box;

private:
    std::pair<std::vector<float>, int> generateVertexData();
};


#endif
