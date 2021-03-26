#ifndef _PLAYER_H
#define _PLAYER_H

#include "character.h"

class Player : public Character
{
public:
    Player(int window_width, int window_height, float speed=1.5);
    bool updateActiveCell(std::pair<int, glm::vec3> new_cell);
};


#endif
