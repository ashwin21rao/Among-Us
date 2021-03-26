#ifndef _PLAYER_H
#define _PLAYER_H

#include "movable_sprite.h"
#include <vector>
#include "util.h"

class Player
{
public:
    Player(int window_width, int window_height, float speed=1.5);
    MovableSprite sprite;

    void translate(int key, float render_time);
    void moveTo(glm::vec3 position);

    float width, height;
    bounding_box b_box;

private:
    std::pair<std::vector<float>, int> generateVertexData();
};


#endif
