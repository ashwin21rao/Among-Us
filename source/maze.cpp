#include "maze.h"
#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
#include <queue>
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

    // add random edges
    std::uniform_int_distribution<int> random_cell(0, number_of_cells);
    int i = 0;
    while (i < 10)
    {
        int cell = random_cell(gen);
        std::uniform_int_distribution<int> random_edge(0, 3);

        // top
        if (random_edge(gen) == 0 && cell >= width)
        {
            if (find(mazeGraph[cell].begin(), mazeGraph[cell].end(), cell - width) == mazeGraph[cell].end())
            {
                mazeGraph[cell].push_back(cell - width);
                mazeGraph[cell - width].push_back(cell);
                i++;
            }
        }

        // right
        if (random_edge(gen) == 1 && (cell + 1) % width != 0)
        {
            if (find(mazeGraph[cell].begin(), mazeGraph[cell].end(), cell + 1) == mazeGraph[cell].end())
            {
                mazeGraph[cell].push_back(cell + 1);
                mazeGraph[cell + 1].push_back(cell);
                i++;
            }
        }

        // bottom
        if (random_edge(gen) == 2 && cell < number_of_cells - width)
        {
            if (find(mazeGraph[cell].begin(), mazeGraph[cell].end(), cell + width) == mazeGraph[cell].end())
            {
                mazeGraph[cell].push_back(cell + width);
                mazeGraph[cell + width].push_back(cell);
                i++;
            }
        }

        // left
        if (random_edge(gen) == 3 && cell % width != 0)
        {
            if (find(mazeGraph[cell].begin(), mazeGraph[cell].end(), cell - 1) == mazeGraph[cell].end())
            {
                mazeGraph[cell].push_back(cell - 1);
                mazeGraph[cell - 1].push_back(cell);
                i++;
            }
        }
    }
}

std::vector<std::pair<int, glm::vec3>> Maze::findShortestPath(int start, int finish)
{
    std::queue<int> q;
    std::vector<bool> visited(number_of_cells, false);
    std::vector<int> prev(number_of_cells);

    std::vector<std::pair<int, glm::vec3>> path;

    visited[start] = true;
    q.push(start);
    while (!q.empty())
    {
        int node = q.front();
        if (node == finish)
            break;

        q.pop();
        for (auto next : mazeGraph[node])
        {
            if (!visited[next])
            {
                visited[next] = true;
                prev[next] = node;
                q.push(next);
            }
        }
    }

    int node = finish;
    while(node != start)
    {
        path.push_back(cells[node]);
        node = prev[node];
    }
    path.push_back(cells[start]);

    std::reverse(path.begin(), path.end());

//    std::cout << "Hereeeeee" << std::endl;
//    for (auto i : path)
//        std::cout << i.first << " ";
//    std::cout << std::endl;

    return path;
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
    std::vector<float> exit_color = {0.0, 0.81, 0.08};

    std::vector<int> adj_cells = mazeGraph[vertex_num];

    auto x = (2 * cell_thickness + cell_size) * (float)c;
    auto y = -(2 * cell_thickness + cell_size) * (float)r;

    float t = cell_thickness * 2;
    int num_vertices = 0;

    // top line
    if (find(adj_cells.begin(), adj_cells.end(), vertex_num - width) == adj_cells.end())
    {
        float p = (float)(r == 0) * cell_thickness;
        generateTrianglesFromPolygon(vertices, {x - cell_size/2 - t, y + cell_size/2 + cell_thickness + p, 0.0f,
                                                x + cell_size/2 + t, y + cell_size/2 + cell_thickness + p, 0.0f,
                                                x + cell_size/2 + t, y + cell_size/2, 0.0f,
                                                x - cell_size/2 - t, y + cell_size/2, 0.0f,},
                                     (vertex_num == exit_cell.first && exit_cell.first == 0) ? exit_color : wall_color);

        num_vertices += 6;
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
                                                x + cell_size/2,  y - cell_size/2 - t, 0.0f},
                                     (vertex_num == exit_cell.first && exit_cell.first == number_of_cells - 1) ? exit_color : wall_color);

        num_vertices += 6;
        walls.push_back({x + cell_size/2, y + cell_size/2 + t, cell_thickness + p, cell_size + 2 * t});
    }

    // bottom line
    if (find(adj_cells.begin(), adj_cells.end(), vertex_num + width) == adj_cells.end())
    {
        float p = (float)(r == height - 1) * cell_thickness;
        generateTrianglesFromPolygon(vertices, {x - cell_size/2 - t, y - cell_size/2, 0.0f,
                                                x + cell_size/2 + t, y - cell_size/2, 0.0f,
                                                x + cell_size/2 + t, y - cell_size/2 - cell_thickness - p, 0.0f,
                                                x - cell_size/2 - t, y - cell_size/2 - cell_thickness - p, 0.0f},
                                     (vertex_num == exit_cell.first && exit_cell.first == number_of_cells - 1) ? exit_color : wall_color);

        num_vertices += 6;
        walls.push_back({x - cell_size/2 - t, y - cell_size/2, cell_size + 2 * t, cell_thickness + p});
    }

    // left line
    if (std::find(adj_cells.begin(), adj_cells.end(), vertex_num - 1) == adj_cells.end())
    {
        float p = (float)(c == 0) * cell_thickness;
        generateTrianglesFromPolygon(vertices, {x - cell_size/2 - cell_thickness - p, y + cell_size/2 + t, 0.0f,
                                                x - cell_size/2, y + cell_size/2 + t, 0.0f,
                                                x - cell_size/2,  y - cell_size/2 - t, 0.0f,
                                                x - cell_size/2 - cell_thickness - p,  y - cell_size/2 - t, 0.0f},
                                     (vertex_num == exit_cell.first && exit_cell.first == 0) ? exit_color : wall_color);

        num_vertices += 6;
        walls.push_back({x - cell_size/2 - cell_thickness - p, y + cell_size/2 + t,
                         cell_thickness + p, cell_size + 2 * t});

    }

    cells.emplace_back(vertex_num, glm::vec3(x, y, 0.0));
    return num_vertices;
}

std::pair<int, glm::vec3> Maze::getRandomCell()
{
    std::mt19937_64 gen(random_device());
    std::uniform_int_distribution<int> random_cell(1, number_of_cells - 1);

    return cells[random_cell(gen)];
}

glm::vec3 Maze::getRandomPosition()
{
    return getRandomCell().second;
}

std::pair<int, glm::vec3> Maze::findNextCell(std::pair<int, glm::vec3> active_cell, glm::vec3 position) const
{
    glm::vec3 cell_pos = active_cell.second;

    // move to top cell
    if (position.y > cell_pos.y + cell_size / 2)
        return cells[active_cell.first - width];
    // move to bottom cell
    if (position.y < cell_pos.y - cell_size / 2)
        return cells[active_cell.first + width];
    // move to right cell
    if (position.x > cell_pos.x + cell_size / 2)
        return cells[active_cell.first + 1];
    // move to left cell
    if (position.x < cell_pos.x - cell_size / 2)
        return cells[active_cell.first - 1];

    return active_cell;
}

void Maze::openExit()
{
    std::mt19937_64 gen(random_device());
    std::uniform_int_distribution<int> random_exit(0, 1);
    exit_cell = random_exit(gen) == 0 ? cells[0] : cells[number_of_cells - 1];

    std::pair<std::vector<float>, int> vertex_data = generateVertexData();
    sprite.createSprite(vertex_data.first, sizeof(float) * vertex_data.first.size(), vertex_data.second);
}
