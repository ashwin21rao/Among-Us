#ifndef _GAME_H
#define _GAME_H
#include "shader.h"
#include "camera.h"
#include "maze.h"
#include "sprite.h"
#include "movable_sprite.h"
#include "player.h"
#include "imposter.h"
#include "window.h"
#include "util.h"
#include "button.h"
#include "coin.h"
#include "bomb.h"
#include "text_handler.h"

class Game
{
public:
    Game(int window_width, int window_height);
    Player player;
    Imposter imposter;
    Maze maze;
    std::vector<Button> buttons;
    std::vector<Coin> coins;
    std::vector<Bomb> bombs;

    Camera camera;
    std::vector<Shader> shaders;
    TextHandler th;

    bool showStartScreen(Window &window);
    bool showEndScreen(Window &window);
    void start();
    void processInput(Window &window);
    void moveSprites(Window &window, float render_time);
    void renderSprites();
    void tick();
    void handleCollisions();
    bool gameOver();
    bool gameWon();

private:
    void movePlayer(Window &window, float render_time);
    void moveImposter(float render_time);
    void displayText();

    bool checkLeftCollision(bounding_box &b1, bounding_box &b2) const;
    bool checkRightCollision(bounding_box &b1, bounding_box &b2) const;
    bool checkTopCollision(bounding_box &b1, bounding_box &b2) const;
    bool checkBottomCollision(bounding_box &b1, bounding_box &b2) const;
    static bool checkCollision(bounding_box &b1, bounding_box &b2) ;

    float collision_threshold = 0.05;
    int number_of_coins, number_of_bombs;
    int window_width, window_height;

    int score;
    double start_time, time_elapsed, total_time;
    bool game_over;
    bool game_won;
    bool lights_off;
    double dark_start_time;
};

#endif
