#include "util.h"
#include <cmath>

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

int generateCircle(float r, float center_x, float center_y,
                    std::vector<float> &vertices, std::vector<float> color, int num_points, bool semicircle)
{
    float x = center_x + r, y = center_y;

    int n = semicircle ? num_points / 2 : num_points;
    for (int i=1; i<=n; i++)
    {
        float x1 = r * (float)cos(i * 2 * M_PI / num_points);
        float y1 = r * (float)sin(i * 2 * M_PI / num_points) + center_y;

        generateTrianglesFromPolygon(vertices, {x, y, 0.0f,
                                                x1, y1, 0.0f,
                                                0.0f, center_y, 0.0f}, color);

        x = x1, y = y1;
    }

    return 3 * n;
}
