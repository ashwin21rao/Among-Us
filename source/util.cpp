#include "util.h"

void generateTrianglesFromPolygon(std::vector<float> &vertices,
                                  std::vector<float> points, std::vector<float> color)
{
    int num_points = (int)points.size() / 3;
    std::vector<float> point(points.begin(), points.begin() + 3);
    std::vector<float> triangle;

    for (int i = 1; i<num_points-1; i++)
    {
        triangle.clear();
        triangle.insert(triangle.end(), point.begin(), point.end());
        triangle.insert(triangle.end(), color.begin(), color.end());

        triangle.insert(triangle.end(), points.begin() + (3 * i), points.begin() + (3 * i) + 3);
        triangle.insert(triangle.end(), color.begin(), color.end());

        triangle.insert(triangle.end(), points.begin() + (3 * i) + 3, points.begin() + (3 * i) + 6);
        triangle.insert(triangle.end(), color.begin(), color.end());

        vertices.insert(vertices.end(), triangle.begin(), triangle.end());
    }
}
