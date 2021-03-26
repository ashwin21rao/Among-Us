#include "maze.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include "util.h"
#include "player.h"

Maze::Maze(int width, int height, int window_width, int window_height): width(width), height(height),
                                                                        sprite(window_width, window_height)
{
    cell_size = 1;
    cell_thickness = 0.05;
    number_of_cells = width * height;

    generateMazeGraph();
    std::pair<std::vector<float>, int> vertex_data = generateVertexData();

//    for (int i=0; i<vertex_data.first.size(); i++)
//    {
//        std::cout << vertex_data.first[i] << " ";
//        if ((i+1) % 6 == 0)
//            std::cout << std::endl;
//    }
//    std::cout << vertex_data.second << std::endl;

    sprite.createSprite(vertex_data.first, sizeof(float) * vertex_data.first.size(), vertex_data.second);
}

int Maze::findRoot(int node, std::vector<int> &parent)
{
    if(parent[node] == node)
        return(node);
    return (parent[node] = findRoot(parent[node], parent));
}

bool Maze::findUnion(int node1, int node2, std::vector<int> &parent)
{
    int root1 = findRoot(node1, parent);
    int root2 = findRoot(node2, parent);
    if(root1 != root2)
    {
        parent[root2] = root1;
        return true;
    }
    return false;
}

void Maze::generateMazeGraph()
{
    int num_vertices = width * height;
    int num_edges = (width - 1) * height + (height - 1) * width;
    std::vector<std::vector<int>> edgeList;
    std::vector<int> parent;
    mazeGraph.resize(num_vertices);

    std::mt19937_64 gen(random_device());
    std::uniform_int_distribution<int> random_dist(-500, 500);

    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            int pos = i * width + j;
            if (j < width - 1)
                edgeList.push_back({random_dist(gen), pos, pos + 1});
            if (i < height - 1)
                edgeList.push_back({random_dist(gen), pos, pos + width});
        }
    }

    for(int i=0; i<num_vertices; i++)
        parent.push_back(i);
    std::sort(edgeList.begin(), edgeList.end());

    int count = 0;
    std::vector<int> edge;
    for(int i=0; i<num_edges; i++)
    {
        edge = edgeList[i];
        if(findUnion(edge[1], edge[2], parent))
        {
            mazeGraph[edge[1]].push_back(edge[2]);
            mazeGraph[edge[2]].push_back(edge[1]);
            count++;
        }
        if(count == num_vertices - 1)
            break;
    }

//    for (int i=0; i<num_vertices; i++)
//    {
//        std::cout << i << ": ";
//        for (auto &node : mazeGraph[i])
//            std::cout << node << " ";
//        std::cout << std::endl;
//    }
}

std::pair<std::vector<float>, int> Maze::generateVertexData()
{
    std::vector<float> vertices;
    int num_vertices = 0;

    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
            num_vertices += createCell(i, j, vertices);
        }
    }

    return {vertices, num_vertices};
}

int Maze::createCell(int r, int c, std::vector<float> &vertices)
{
    int vertex_num = width * r + c;
    std::vector<int> adj_cells = mazeGraph[vertex_num];

    auto x = (2 * cell_thickness + cell_size) * (float)c;
    auto y = -(2 * cell_thickness + cell_size) * (float)r;

    std::vector<bool> sides(4, false);
    std::vector<bounding_box> cell_walls(4);

    float t = cell_thickness * 2;
    int num_vertices = 0;

    // top line
    if (find(adj_cells.begin(), adj_cells.end(), vertex_num - width) == adj_cells.end())
    {
        float p = (float)(r == 0) * cell_thickness;
        generateTrianglesFromPolygon(vertices, {x - cell_size/2 - t, y + cell_size/2 + cell_thickness + p, 0.0f,
                                                x + cell_size/2 + t, y + cell_size/2 + cell_thickness + p, 0.0f,
                                                x + cell_size/2 + t, y + cell_size/2, 0.0f,
                                                x - cell_size/2 - t, y + cell_size/2, 0.0f,}, wall_color);

        num_vertices += 6;
        sides[0] = true;
        walls.push_back({x - cell_size/2 - t, y + cell_size/2 + cell_thickness + p,
                         cell_size + 2 * t, cell_thickness + p});
    }

    // right line
    if (find(adj_cells.begin(), adj_cells.end(), vertex_num + 1) == adj_cells.end())
    {
        float p = (float)(c == width - 1) * cell_thickness;
        generateTrianglesFromPolygon(vertices, {x + cell_size/2, y + cell_size/2 + t, 0.0f,
                                                x + cell_size/2 + cell_thickness + p, y + cell_size/2 + t, 0.0f,
                                                x + cell_size/2 + cell_thickness + p,  y - cell_size/2 - t, 0.0f,
                                                x + cell_size/2,  y - cell_size/2 - t, 0.0f}, wall_color);

        num_vertices += 6;
        sides[1] = true;
        walls.push_back({x + cell_size/2, y + cell_size/2 + t, cell_thickness + p, cell_size + 2 * t});
    }

    // bottom line
    if (find(adj_cells.begin(), adj_cells.end(), vertex_num + width) == adj_cells.end())
    {
        float p = (float)(r == height - 1) * cell_thickness;
        generateTrianglesFromPolygon(vertices, {x - cell_size/2 - t, y - cell_size/2, 0.0f,
                                                x + cell_size/2 + t, y - cell_size/2, 0.0f,
                                                x + cell_size/2 + t, y - cell_size/2 - cell_thickness - p, 0.0f,
                                                x - cell_size/2 - t, y - cell_size/2 - cell_thickness - p, 0.0f,}, wall_color);

        num_vertices += 6;
        sides[2] = true;
        walls.push_back({x - cell_size/2 - t, y - cell_size/2, cell_size + 2 * t, cell_thickness + p});
    }

    // left line
    if (std::find(adj_cells.begin(), adj_cells.end(), vertex_num - 1) == adj_cells.end())
    {
        float p = (float)(c == 0) * cell_thickness;
        generateTrianglesFromPolygon(vertices, {x - cell_size/2 - cell_thickness - p, y + cell_size/2 + t, 0.0f,
                                                x - cell_size/2, y + cell_size/2 + t, 0.0f,
                                                x - cell_size/2,  y - cell_size/2 - t, 0.0f,
                                                x - cell_size/2 - cell_thickness - p,  y - cell_size/2 - t, 0.0f}, wall_color);

        num_vertices += 6;
        sides[3] = true;
        walls.push_back({x - cell_size/2 - cell_thickness - p, y + cell_size/2 + t,
                         cell_thickness + p, cell_size + 2 * t});

    }

    cells.push_back({sides, {x, y}});
    return num_vertices;
}

void Maze::render() const
{
    sprite.render();
}

std::pair<std::vector<bool>, std::pair<float, float>> Maze::getRandomCell()
{
    std::mt19937_64 gen(random_device());
    std::uniform_int_distribution<int> random_dist(0, number_of_cells);

    return cells[random_dist(gen)];
}

glm::vec3 Maze::getRandomPosition()
{
    std::pair<std::vector<bool>, std::pair<float, float>> cell = getRandomCell();
    return glm::vec3(cell.second.first, cell.second.second, 0.0);
}
