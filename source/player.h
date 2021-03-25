#ifndef _PLAYER_H
#define _PLAYER_H
#include "movable_sprite.h"
#include <vector>

class Player
{
public:
    Player(int window_width, int window_height, float speed=1.5);
    MovableSprite sprite;
private:
    static std::pair<std::vector<float>, int> generateVertexData();
};


#endif
