#ifndef _GAME_H
#define _GAME_H
#include "shader.h"
#include "shape.h"
#include "camera.h"
#include "maze.h"
#include "sprite.h"
#include "movable_sprite.h"
#include "player.h"
#include "window.h"

class Game
{
public:
    Game(int window_width, int window_height);
    Player player;
    Maze maze;
    Camera camera;
    Shader shader;
    std::vector<Sprite*> sprite_list;

    void renderSprites();
    void movePlayer(Window &window, float render_time);
};


#endif
