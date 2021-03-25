#ifndef MOVABLE_SPRITE_H
#define MOVABLE_SPRITE_H
#include "sprite.h"

class MovableSprite: public Sprite
{
public:
    MovableSprite(int window_width, int window_height, float speed=1.5);
    void translate(int key, float render_time);
    float speed;
};


#endif
