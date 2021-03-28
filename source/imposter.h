#ifndef _IMPOSTER_H
#define _IMPOSTER_H

#include "character.h"
#include <vector>

class Imposter : public Character
{
public:
    Imposter(int window_width, int window_height, float speed=1.5);
    void move(int maze_width, float render_time);
    void updatePath(std::vector<std::pair<int, glm::vec3>> path);
    void updateActiveCell(std::pair<int, glm::vec3> new_cell);

    std::pair<int, glm::vec3> next_cell;

    void kill();
    bool isAlive() const;

private:
    std::vector<std::pair<int, glm::vec3>> path_to_player;
    int current_pos;  // current position in path
    bool dead = false;
};


#endif
