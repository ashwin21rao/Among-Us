#include "imposter.h"
#include <iostream>
#include <glm/gtc/epsilon.hpp>

Imposter::Imposter(int window_width, int window_height, float speed)
        : Character(window_width, window_height, {{0.8, 0.0, 0.0}, {0.7, 0.0, 0.0}, {0.65, 0.0, 0.0}}, speed)
{

}

char Imposter::findDirection(int maze_width)
{
    if (next_cell.first == active_cell.first + 1)
        return 'r';
    else if (next_cell.first == active_cell.first - 1)
        return 'l';
    else if (next_cell.first == active_cell.first + maze_width)
        return 'd';
    else if (next_cell.first == active_cell.first - maze_width)
        return 'u';
    else
        return 0;
}

void Imposter::move(int maze_width, float render_time)
{
    if (current_pos == 0 && retrace_dir)
    {
        translate(retrace_dir, render_time);

        glm::vec3 p = glm::epsilonEqual(sprite.getPosition(), active_cell.second, glm::vec3(0.05));
        if(p.x && p.y)
        {
            sprite.moveTo(active_cell.second);
            retrace_dir = 0;
        }
        return;
    }

    translate(findDirection(maze_width), render_time);
}

void Imposter::updatePath(std::vector<std::pair<int, glm::vec3>> path, int maze_width)
{
    if((abs(next_cell.first - active_cell.first) == 1 && abs(path[1].first - active_cell.first) == maze_width) ||
       (abs(next_cell.first - active_cell.first) == maze_width && abs(path[1].first - active_cell.first) == 1))
    {
//        sprite.moveTo(active_cell.second);
        if (retrace_dir == 0)
        {
            char dir = findDirection(maze_width);
            if (dir == 'r') retrace_dir = 'l';
            else if (dir == 'l') retrace_dir = 'r';
            else if (dir == 'u') retrace_dir = 'd';
            else if (dir == 'd') retrace_dir = 'u';
        }
    }

    path_to_player = std::move(path);
    current_pos = 0;
    next_cell = path_to_player[current_pos + 1];
}

void Imposter::updateActiveCell(std::pair<int, glm::vec3> new_cell)
{
    if (active_cell != new_cell)
    {
        current_pos++;
        active_cell = new_cell;
        next_cell = path_to_player[current_pos + 1];
        sprite.moveTo(active_cell.second);
    }
}

void Imposter::kill()
{
    dead = true;
}

void Imposter::revive()
{
    dead = false;
}

bool Imposter::isAlive() const
{
    return !dead;
}
