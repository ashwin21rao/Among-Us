#ifndef _UTIL_H
#define _UTIL_H

#include <vector>

struct bounding_box {
    float x;
    float y;
    float width;
    float height;
};

void generateTrianglesFromPolygon(std::vector<float> &vertices,
                                  std::vector<float> points, std::vector<float> color);

int generateCircle(float radius, float center_x, float center_y,
                    std::vector<float> &vertices, std::vector<float> color, int num_points = 26, bool semicircle=false);

#endif
