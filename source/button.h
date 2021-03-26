#ifndef _BUTTON_H
#define _BUTTON_H

#include "sprite.h"
#include "util.h"

class Button
{
public:
    Button(int window_width, int window_height, std::vector<float> color);
    Sprite sprite;

    void moveTo(glm::vec3 position);

    bounding_box b_box;

private:
    std::pair<std::vector<float>, int> generateVertexData();
    std::vector<float> color;
};


#endif
