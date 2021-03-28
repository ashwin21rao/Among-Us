#include "imposter.h"

Imposter::Imposter(int window_width, int window_height, float speed)
        : Character(window_width, window_height, {{0.8, 0.0, 0.0}, {0.7, 0.0, 0.0}, {0.65, 0.0, 0.0}}, speed)
{

}

void Imposter::move(int maze_width, float render_time)
{
    if (next_cell.first == active_cell.first + 1)
        translate('r', render_time);
    else if (next_cell.first == active_cell.first - 1)
        translate('l', render_time);
    else if (next_cell.first == active_cell.first + maze_width)
        translate('d', render_time);
    else if (next_cell.first == active_cell.first - maze_width)
        translate('u', render_time);
}

void Imposter::updatePath(std::vector<std::pair<int, glm::vec3>> path)
{
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
    }
}

void Imposter::kill()
{
    dead = true;
}

bool Imposter::isAlive() const
{
    return !dead;
}
