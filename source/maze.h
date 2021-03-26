#ifndef _MAZE_H
#define _MAZE_H
#include <vector>
#include <random>
#include "sprite.h"
#include "player.h"
#include "util.h"

class Maze
{
public:
    Maze(int width, int height, int window_width, int window_height);
    Sprite sprite;

    // dimensions of maze cells
    float cell_size, cell_thickness;

    // walls of maze
    std::vector<bounding_box> walls;

    // render maze
    void render() const;

    // other functions
    std::pair<std::vector<bool>, std::pair<float, float>> getRandomCell();
    glm::vec3 getRandomPosition();

private:
    int width, height;
    int number_of_cells;

    // seed for random data
    std::random_device random_device;

    // maze graph data
    std::vector<std::vector<int>> mazeGraph;

    // cells of maze
    std::vector<std::pair<std::vector<bool>, std::pair<float, float>>> cells;
    std::vector<float> wall_color = {0.25, 0.25, 0.25};

    // generating maze graph
    int findRoot(int node, std::vector<int> &parent);
    bool findUnion(int node1, int node2, std::vector<int> &parent);
    void generateMazeGraph();

    // generating maze from graph
    std::pair<std::vector<float>, int> generateVertexData();
    int createCell(int r, int c, std::vector<float> &vertices);

    // other functions
};

#endif
