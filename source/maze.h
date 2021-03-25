#ifndef _MAZE_H
#define _MAZE_H
#include <vector>
#include <random>
#include "sprite.h"

class Maze
{
public:
    Maze(int width, int height, int window_width, int window_height);
    Sprite sprite;

    // render maze
    void render() const;

    // other functions
    glm::vec3 getStartPosition();

private:
    int width, height;
    float cell_size, cell_thickness;
    int number_of_cells;

    // seed for random data
    std::random_device random_device;

    // maze graph data
    std::vector<std::vector<int>> mazeGraph;

    // cells of maze
    std::vector<std::pair<float, float>> cells;

    // generating maze graph
    int findRoot(int node, std::vector<int> &parent);
    bool findUnion(int node1, int node2, std::vector<int> &parent);
    void generateMazeGraph();

    // generating maze from graph
    std::pair<std::vector<float>, int> generateVertexData();
    int createCell(int r, int c, std::vector<float> &vertices);

    // other functions
    std::pair<float, float> getRandomCell();
};

#endif
