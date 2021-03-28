#ifndef _COIN_H
#define _COIN_H

#include "sprite.h"
#include "util.h"

class Coin
{
public:
    Coin(int window_width, int window_height);
    Sprite sprite;

    void moveTo(glm::vec3 position);

    bounding_box b_box;

private:
    std::pair<std::vector<float>, int> generateVertexData();
};


#endif
