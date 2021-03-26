#ifndef _MAZE_H
#define _MAZE_H
#include <vector>
#include <random>
#include "sprite.h"
#include "util.h"

class Maze
{
public:
    Maze(int width, int height, int window_width, int window_height);
    Sprite sprite;

    // dimensions of maze
    int width, height;

    // dimensions of maze cells
    float cell_size, cell_thickness;

    // walls of maze
    std::vector<bounding_box> walls;

    // other functions
    std::pair<int, glm::vec3> getRandomCell();
    std::pair<int, glm::vec3> findNextCell(std::pair<int, glm::vec3> active_cell, glm::vec3 position) const;
    std::vector<std::pair<int, glm::vec3>> findShortestPath(int start, int finish);

private:
    int number_of_cells;

    // seed for random data
    std::random_device random_device;

    // maze graph data
    std::vector<std::vector<int>> mazeGraph;

    // cells of maze
    std::vector<std::pair<int, glm::vec3>> cells;
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
