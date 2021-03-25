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

    float t = cell_thickness * 2;
    int num_vertices = 0;

    // top line
    if (find(adj_cells.begin(), adj_cells.end(), vertex_num - width) == adj_cells.end())
    {
        float p = (float)(r == 0) * cell_thickness;
        generateTrianglesFromPolygon(vertices, {x - cell_size/2 - t, y + cell_size/2 + cell_thickness + p, 0.0f,
                                                x + cell_size/2 + t, y + cell_size/2 + cell_thickness + p, 0.0f,
                                                x + cell_size/2 + t, y + cell_size/2, 0.0f,
                                                x - cell_size/2 - t, y + cell_size/2, 0.0f,}, {0.0f, 0.0f, 0.0f});

        num_vertices += 6;
        sides[0] = true;
        walls.emplace_back(x - cell_size/2 - t, y + cell_size/2 + cell_thickness + p);
    }

    // right line
    if (find(adj_cells.begin(), adj_cells.end(), vertex_num + 1) == adj_cells.end())
    {
        float p = (float)(c == width - 1) * cell_thickness;
        generateTrianglesFromPolygon(vertices, {x + cell_size/2, y + cell_size/2 + t, 0.0f,
                                                x + cell_size/2 + cell_thickness + p, y + cell_size/2 + t, 0.0f,
                                                x + cell_size/2 + cell_thickness + p,  y - cell_size/2 - t, 0.0f,
                                                x + cell_size/2,  y - cell_size/2 - t, 0.0f}, {0.0f, 0.0f, 0.0f});

        num_vertices += 6;
        sides[1] = true;
        walls.emplace_back(x + cell_size/2, y + cell_size/2 + t);
    }

    // bottom line
    if (find(adj_cells.begin(), adj_cells.end(), vertex_num + width) == adj_cells.end())
    {
        float p = (float)(r == height - 1) * cell_thickness;
        generateTrianglesFromPolygon(vertices, {x - cell_size/2 - t, y - cell_size/2, 0.0f,
                                                x + cell_size/2 + t, y - cell_size/2, 0.0f,
                                                x + cell_size/2 + t, y - cell_size/2 - cell_thickness - p, 0.0f,
                                                x - cell_size/2 - t, y - cell_size/2 - cell_thickness - p, 0.0f,}, {0.0f, 0.0f, 0.0f});

        num_vertices += 6;
        sides[2] = true;
        walls.emplace_back(x - cell_size/2 - t, y - cell_size/2);
    }

    // left line
    if (std::find(adj_cells.begin(), adj_cells.end(), vertex_num - 1) == adj_cells.end())
    {
        float p = (float)(c == 0) * cell_thickness;
        generateTrianglesFromPolygon(vertices, {x - cell_size/2 - cell_thickness - p, y + cell_size/2 + t, 0.0f,
                                                x - cell_size/2, y + cell_size/2 + t, 0.0f,
                                                x - cell_size/2,  y - cell_size/2 - t, 0.0f,
                                                x - cell_size/2 - cell_thickness - p,  y - cell_size/2 - t, 0.0f}, {0.0f, 0.0f, 0.0f});

        num_vertices += 6;
        sides[3] = true;
        walls.emplace_back(x - cell_size/2 - cell_thickness - p, y + cell_size/2 + t);
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

void Maze::findNextCell(Player &player)
{
    glm::vec3 pos = player.sprite.getPosition();
    float cell_x = player.active_cell.second.first;
    float cell_y = player.active_cell.second.second;
    int cell_num = find(cells.begin(), cells.end(), player.active_cell) - cells.begin();

//    std::cout << "Hereeeee" << cell_x << " " << cell_y << std::endl;

//    for (int i=0; i<cells.size(); i++)
//    {
//        std::cout << cells[i].second.first << " " << cells[i].second.second << std::endl;
//        if (cells[i].second.first == cell_x && cells[i].second.second == cell_y)
//        {
//            cell_num = i;
//            break;
//        }
//    }

    std::cout << "Cell = " << cell_num << std::endl;

//    std::cout << pos.x << " " << pos.y << std::endl;


    // no top wall
    if (!player.active_cell.first[0])
    {
        std::cout << "No top" << cell_num - width << std::endl;
        if (pos.y - player.height / 2 > cell_y + cell_size / 2)
            player.active_cell = cells[cell_num - width];
    }

    // no bottom wall
    if (!player.active_cell.first[2])
    {
        std::cout << "No bottom" << cell_num + width << std::endl;
        if (pos.y + player.height / 2 < cell_y - cell_size / 2)
            player.active_cell = cells[cell_num + width];
    }

    // no left wall
    if (!player.active_cell.first[3])
    {
        std::cout << "No left" << cell_num - 1 << std::endl;
        if (pos.x + player.width / 2 < cell_x - cell_size / 2)
            player.active_cell = cells[cell_num - 1];
    }

    // no right wall
    if (!player.active_cell.first[1])
    {
        std::cout << "No right" << cell_num + 1 << std::endl;
        if (pos.x - player.width / 2 > cell_x + cell_size / 2)
            player.active_cell = cells[cell_num + 1];
    }
}

void Maze::checkWallCollision(Player &player)
{
    glm::vec3 pos = player.sprite.getPosition();

    float p_x = pos.x + player.height / 2;
    float p_y = pos.y - player.width / 2;
}


//void Maze::createCell(int r, int c)
//{
//    int vertex_num = width * r + c;
//    std::vector<int> adj_cells = mazeGraph[vertex_num];
//    auto x = (float)c, y = -(float)r;
//
//    // top line
//    if (std::find(adj_cells.begin(), adj_cells.end(), vertex_num - width) == adj_cells.end())
//    {
//        generateTrianglesFromPolygon(vertices, {x, y, 0.0f,
//                                                x + cell_size, y, 0.0f,
//                                                x + cell_size,  y - cell_thickness, 0.0f,
//                                                x,  y - cell_thickness, 0.0f}, {0.0f, 0.0f, 0.0f});
//
//        vertices_data.first += 6;
//        std::cout << "top" << std::endl;
//    }
//
//    // right line
//    if (find(adj_cells.begin(), adj_cells.end(), vertex_num + 1) == adj_cells.end())
//    {
//        generateTrianglesFromPolygon(vertices, {x + cell_size - cell_thickness, y, 0.0f,
//                                                x + cell_size, y, 0.0f,
//                                                x + cell_size,  y - cell_size, 0.0f,
//                                                x + cell_size - cell_thickness,  y - cell_size, 0.0f}, {0.0f, 0.0f, 0.0f});
//
//        vertices_data.first += 6;
//        std::cout << "right" << std::endl;
//    }
//
//    // bottom line
//    if (find(adj_cells.begin(), adj_cells.end(), vertex_num + width) == adj_cells.end())
//    {
//        generateTrianglesFromPolygon(vertices, {x, y - cell_size + cell_thickness, 0.0f,
//                                                x + cell_size, y - cell_size + cell_thickness, 0.0f,
//                                                x + cell_size,  y - cell_size, 0.0f,
//                                                x,  y - cell_size, 0.0f}, {0.0f, 0.0f, 0.0f});
//
//        vertices_data.first += 6;
//        std::cout << "bottom" << std::endl;
//    }
//
//    // left line
//    if (find(adj_cells.begin(), adj_cells.end(), vertex_num - 1) == adj_cells.end())
//    {
//        generateTrianglesFromPolygon(vertices, {x, y, 0.0f,
//                                                x + cell_thickness, y, 0.0f,
//                                                x + cell_thickness,  y - cell_size, 0.0f,
//                                                x,  y - cell_size, 0.0f}, {0.0f, 0.0f, 0.0f});
//
//        vertices_data.first += 6;
//        std::cout << "left" << std::endl;
//    }
//}