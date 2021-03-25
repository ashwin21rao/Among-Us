#ifndef _PLAYER_H
#define _PLAYER_H
#include "movable_sprite.h"
#include <vector>

class Player
{
public:
    Player(int window_width, int window_height, float speed=1.5);
    MovableSprite sprite;
    void setInitialCell(std::pair<std::vector<bool>, std::pair<float, float>> cell);
    std::vector<int> checkWallCollision(float cell_size);

    std::pair<std::vector<bool>, std::pair<float, float>> active_cell;
    float width, height;

private:
    std::pair<std::vector<float>, int> generateVertexData();
};


#endif
