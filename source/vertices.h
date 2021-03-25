#ifndef _VERTICES_H
#define _VERTICES_H

#include <vector>

enum ShapeType {
    DODECAHEDRON,
    ICOSAHEDRON,
    ELONGATED_SQUARE_BIPYRAMID,
    HEXAGONAL_BIPYRAMID,
    UNDECAGONAL_PYRAMID,
    DECAGONAL_PRISM
};

void generateTrianglesFromPolygon1(std::vector<float> &vertices,
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

std::pair<int, float> getVertexData(std::vector<float> &vertices, ShapeType shape)
{
    int num_vertices = 0;
    float scaling_factor = 1;

    if (shape == ELONGATED_SQUARE_BIPYRAMID)
    {
        num_vertices = 48;

        // top face
        generateTrianglesFromPolygon1(vertices, {-0.5f, -0.5f, -0.5f,
                                                 0.5f, -0.5f, -0.5f,
                                                 0.5f,  0.5f, -0.5f,
                                                -0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f});
        // bottom face
        generateTrianglesFromPolygon1(vertices, {-0.5f, -0.5f, 0.5f,
                                                 0.5f, -0.5f, 0.5f,
                                                 0.5f,  0.5f, 0.5f,
                                                -0.5f,  0.5f, 0.5f}, {0.0f, 1.0f, 0.0f});
        // left face
        generateTrianglesFromPolygon1(vertices, {-0.5f,  0.5f,  0.5f,
                                                -0.5f,  0.5f, -0.5f,
                                                -0.5f, -0.5f, -0.5f,
                                                -0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 1.0f});
        // right face
        generateTrianglesFromPolygon1(vertices, {0.5f,  0.5f,  0.5f,
                                                0.5f,  0.5f, -0.5f,
                                                0.5f, -0.5f, -0.5f,
                                                0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 0.0f});
        // top pyramid
        generateTrianglesFromPolygon1(vertices, {0.5f,    0.5f,  0.5f,
                                                0.5f,    0.5f, -0.5f,
                                                0.0f, 1.2071f,  0.0f}, {0.5f, 0.0f, 0.0f});
        generateTrianglesFromPolygon1(vertices, { 0.5f,    0.5f, -0.5f,
                                                -0.5f,    0.5f, -0.5f,
                                                 0.0f, 1.2071f,  0.0f}, {0.0f, 0.5f, 0.0f});
        generateTrianglesFromPolygon1(vertices, {-0.5f,    0.5f, -0.5f,
                                                -0.5f,    0.5f,  0.5f,
                                                 0.0f, 1.2071f,  0.0f}, {0.0f, 0.0f, 0.5f});
        generateTrianglesFromPolygon1(vertices, {-0.5f,    0.5f, 0.5f,
                                                 0.5f,    0.5f, 0.5f,
                                                 0.0f, 1.2071f, 0.0f}, {0.5f, 0.0f, 0.5f});

        // bottom pyramid
        generateTrianglesFromPolygon1(vertices, {0.5f,    -0.5f,  0.5f,
                                                0.5f,    -0.5f, -0.5f,
                                                0.0f, -1.2071f,  0.0f}, {0.5f, 0.0f, 0.0f});
        generateTrianglesFromPolygon1(vertices, { 0.5f,    -0.5f, -0.5f,
                                                -0.5f,    -0.5f, -0.5f,
                                                 0.0f, -1.2071f,  0.0f}, {0.0f, 0.5f, 0.0f});
        generateTrianglesFromPolygon1(vertices, {-0.5f,    -0.5f, -0.5f,
                                                -0.5f,    -0.5f,  0.5f,
                                                 0.0f, -1.2071f,  0.0f}, {0.0f, 0.0f, 0.5f});
        generateTrianglesFromPolygon1(vertices, {-0.5f,    -0.5f, 0.5f,
                                                 0.5f,    -0.5f, 0.5f,
                                                 0.0f, -1.2071f, 0.0f}, {0.5f, 0.0f, 0.5f});
    }

    else if (shape == HEXAGONAL_BIPYRAMID)
    {
        num_vertices = 36;

        // top pyramid
        generateTrianglesFromPolygon1(vertices, {1.0000f, 0.0f, 0.0000f,
                                                0.5000f, 0.0f, 0.8660f,
                                                   0.0f, 1.0f,    0.0f}, {1.0f, 0.0f, 0.0f});
        generateTrianglesFromPolygon1(vertices, { 0.5000f, 0.0f, 0.8660f,
                                                -0.5000f, 0.0f, 0.8660f,
                                                    0.0f, 1.0f,    0.0f}, {0.5f, 0.0f, 0.5f});
        generateTrianglesFromPolygon1(vertices, {-0.5000f, 0.0f, 0.8660f,
                                                -1.0000f, 0.0f, 0.0000f,
                                                    0.0f, 1.0f,    0.0f}, {0.0f, 0.5f, 0.5f});
        generateTrianglesFromPolygon1(vertices, {-1.0000f, 0.0f,  0.0000f,
                                                -0.5000f, 0.0f, -0.8660f,
                                                    0.0f, 1.0f,    0.0f}, {0.4f, 0.2f, 0.2f});
        generateTrianglesFromPolygon1(vertices, {-0.5000f, 0.0f, -0.8660f,
                                                 0.5000f, 0.0f, -0.8660f,
                                                    0.0f, 1.0f,     0.0f}, {1.0f, 1.0f, 0.0f});
        generateTrianglesFromPolygon1(vertices, {0.5000f, 0.0f, -0.8660f,
                                                1.0000f, 0.0f,  0.0000f,
                                                   0.0f, 1.0f,     0.0f}, {0.0f, 0.5f, 0.0f});

        // bottom pyramid
        generateTrianglesFromPolygon1(vertices, {1.0000f,  0.0f, 0.0000f,
                                                0.5000f,  0.0f, 0.8660f,
                                                   0.0f, -1.0f,    0.0f}, {0.5f, 0.5f, 0.5f});
        generateTrianglesFromPolygon1(vertices, { 0.5000f,  0.0f, 0.8660f,
                                                -0.5000f,  0.0f, 0.8660f,
                                                    0.0f, -1.0f,    0.0f}, {0.5f, 1.0f, 0.5f});
        generateTrianglesFromPolygon1(vertices, {-0.5000f,  0.0f, 0.8660f,
                                                -1.0000f,  0.0f, 0.0000f,
                                                    0.0f, -1.0f,    0.0f}, {1.0f, 0.5f, 0.5f});
        generateTrianglesFromPolygon1(vertices, {-1.0000f,  0.0f,  0.0000f,
                                                -0.5000f,  0.0f, -0.8660f,
                                                    0.0f, -1.0f,    0.0f}, {0.0f, 0.0f, 1.0f});
        generateTrianglesFromPolygon1(vertices, {-0.5000f,  0.0f, -0.8660f,
                                                 0.5000f,  0.0f, -0.8660f,
                                                    0.0f, -1.0f,     0.0f}, {1.0f, 0.0f, 1.0f});
        generateTrianglesFromPolygon1(vertices, {0.5000f,  0.0f, -0.8660f,
                                                1.0000f,  0.0f,  0.0000f,
                                                   0.0f, -1.0f,     0.0f}, {0.5f, 0.0f, 0.0f});
    }
    else if (shape == UNDECAGONAL_PYRAMID)
    {
        num_vertices = 60;

        // base
        generateTrianglesFromPolygon1(vertices, { 1.0000f, 0.0f,  0.0000f,
                                                 0.8413f, 0.0f,  0.5406f,
                                                 0.4154f, 0.0f,  0.9096f,
                                                -0.1423f, 0.0f,  0.9898f,
                                                -0.6549f, 0.0f,  0.7557f,
                                                -0.9595f, 0.0f,  0.2817f,
                                                -0.9595f, 0.0f, -0.2817f,
                                                -0.6549f, 0.0f, -0.7557f,
                                                -0.1423f, 0.0f, -0.9898f,
                                                 0.4154f, 0.0f, -0.9096f,
                                                 0.8413f, 0.0f, -0.5406f}, {0.8f, 0.5f, 0.8f});

        // top pyramid
        generateTrianglesFromPolygon1(vertices, {1.0000f, 0.0f,  0.0000f,
                                                0.8413f, 0.0f,  0.5406f,
                                                0.0f,    1.0f,     0.0f}, {0.5f, 0.0f, 0.0f});
        generateTrianglesFromPolygon1(vertices, {0.8413f, 0.0f,  0.5406f,
                                                0.4154f, 0.0f,  0.9096f,
                                                0.0f,    1.0f,     0.0f}, {0.6f, 0.8f, 0.0f});
        generateTrianglesFromPolygon1(vertices, { 0.4154f, 0.0f,  0.9096f,
                                                -0.1423f, 0.0f,  0.9898f,
                                                 0.0f,    1.0f,     0.0f}, {0.0f, 0.0f, 0.3f});
        generateTrianglesFromPolygon1(vertices, {-0.1423f, 0.0f,  0.9898f,
                                                -0.6549f, 0.0f,  0.7557f,
                                                 0.0f,    1.0f,     0.0f}, {0.0f, 0.6f, 0.0f});
        generateTrianglesFromPolygon1(vertices, {-0.6549f, 0.0f,  0.7557f,
                                                -0.9595f, 0.0f,  0.2817f,
                                                 0.0f,    1.0f,     0.0f}, {0.1f, 0.3f, 0.7f});
        generateTrianglesFromPolygon1(vertices, {-0.9595f, 0.0f,  0.2817f,
                                                -0.9595f, 0.0f, -0.2817f,
                                                 0.0f,    1.0f,     0.0f}, {0.8f, 0.2f, 0.0f});
        generateTrianglesFromPolygon1(vertices, {-0.9595f, 0.0f, -0.2817f,
                                                -0.6549f, 0.0f, -0.7557f,
                                                 0.0f,    1.0f,     0.0f}, {0.3f, 0.5f, 0.7f});
        generateTrianglesFromPolygon1(vertices, {-0.6549f, 0.0f, -0.7557f,
                                                -0.1423f, 0.0f, -0.9898f,
                                                 0.0f,    1.0f,     0.0f}, {0.6f, 0.4f, 0.2f});
        generateTrianglesFromPolygon1(vertices, {-0.1423f, 0.0f, -0.9898f,
                                                 0.4154f, 0.0f, -0.9096f,
                                                 0.0f,    1.0f,     0.0f}, {0.5f, 0.0f, 1.0f});
        generateTrianglesFromPolygon1(vertices, {0.4154f, 0.0f, -0.9096f,
                                                0.8413f, 0.0f, -0.5406f,
                                                0.0f,    1.0f,     0.0f}, {0.0f, 1.0f, 0.5f});
        generateTrianglesFromPolygon1(vertices, {0.8413f, 0.0f, -0.5406f,
                                                1.0000f, 0.0f,  0.0000f,
                                                0.0f,    1.0f,     0.0f}, {0.5f, 0.5f, 1.0f});
    }
    else if (shape == DECAGONAL_PRISM)
    {
        num_vertices = 108;

        // top face
        generateTrianglesFromPolygon1(vertices, { 1.0000f, -0.5f,  0.0000f,
                                                 0.8090f, -0.5f,  0.5878f,
                                                 0.3090f, -0.5f,  0.9511f,
                                                -0.3090f, -0.5f,  0.9511f,
                                                -0.8090f, -0.5f,  0.5878f,
                                                -1.0000f, -0.5f,  0.0000f,
                                                -0.8090f, -0.5f, -0.5878f,
                                                -0.3090f, -0.5f, -0.9511f,
                                                 0.3090f, -0.5f, -0.9511f,
                                                 0.8090f, -0.5f, -0.5878f}, {0.8f, 0.4f, 0.6f});

        // bottom face
        generateTrianglesFromPolygon1(vertices, { 1.0000f, 0.5f,  0.0000f,
                                                 0.8090f, 0.5f,  0.5878f,
                                                 0.3090f, 0.5f,  0.9511f,
                                                -0.3090f, 0.5f,  0.9511f,
                                                -0.8090f, 0.5f,  0.5878f,
                                                -1.0000f, 0.5f,  0.0000f,
                                                -0.8090f, 0.5f, -0.5878f,
                                                -0.3090f, 0.5f, -0.9511f,
                                                 0.3090f, 0.5f, -0.9511f,
                                                 0.8090f, 0.5f, -0.5878f}, {0.6f, 0.4f, 0.8f});

        // side faces
        generateTrianglesFromPolygon1(vertices, {1.0000f,  0.5f,  0.0000f,
                                                0.8090f,  0.5f,  0.5878f,
                                                0.8090f, -0.5f,  0.5878f,
                                                1.0000f, -0.5f,  0.0000f}, {0.2f, 0.6f, 0.8f});
        generateTrianglesFromPolygon1(vertices, {0.8090f,  0.5f,  0.5878f,
                                                0.3090f,  0.5f,  0.9511f,
                                                0.3090f, -0.5f,  0.9511f,
                                                0.8090f, -0.5f,  0.5878f}, {0.8f, 0.0f, 0.0f});
        generateTrianglesFromPolygon1(vertices, { 0.3090f,  0.5f,  0.9511f,
                                                -0.3090f,  0.5f,  0.9511f,
                                                -0.3090f, -0.5f,  0.9511f,
                                                 0.3090f, -0.5f,  0.9511f}, {0.0f, 0.3f, 0.5f});
        generateTrianglesFromPolygon1(vertices, {-0.3090f,  0.5f,  0.9511f,
                                                -0.8090f,  0.5f,  0.5878f,
                                                -0.8090f, -0.5f,  0.5878f,
                                                -0.3090f, -0.5f,  0.9511f}, {0.3f, 0.7f, 0.3f});
        generateTrianglesFromPolygon1(vertices, {-0.8090f,  0.5f,  0.5878f,
                                                -1.0000f,  0.5f,  0.0000f,
                                                -1.0000f, -0.5f,  0.0000f,
                                                -0.8090f, -0.5f,  0.5878f}, {0.6f, 0.3f, 0.2f});
        generateTrianglesFromPolygon1(vertices, {-1.0000f,  0.5f,  0.0000f,
                                                -0.8090f,  0.5f, -0.5878f,
                                                -0.8090f, -0.5f, -0.5878f,
                                                -1.0000f, -0.5f,  0.0000f}, {0.8f, 0.8f, 0.4f});
        generateTrianglesFromPolygon1(vertices, {-0.8090f,  0.5f, -0.5878f,
                                                -0.3090f,  0.5f, -0.9511f,
                                                -0.3090f, -0.5f, -0.9511f,
                                                -0.8090f, -0.5f, -0.5878f}, {0.5f, 0.0f, 0.5f});
        generateTrianglesFromPolygon1(vertices, {-0.3090f,  0.5f, -0.9511f,
                                                 0.3090f,  0.5f, -0.9511f,
                                                 0.3090f, -0.5f, -0.9511f,
                                                -0.3090f, -0.5f, -0.9511f}, {0.8f, 0.3f, 0.0f});
        generateTrianglesFromPolygon1(vertices, {0.3090f,  0.5f, -0.9511f,
                                                0.8090f,  0.5f, -0.5878f,
                                                0.8090f, -0.5f, -0.5878f,
                                                0.3090f, -0.5f, -0.9511f}, {0.1f, 1.0f, 1.0f});
        generateTrianglesFromPolygon1(vertices, {0.8090f,  0.5f, -0.5878f,
                                                1.0000f,  0.5f,  0.0000f,
                                                1.0000f, -0.5f,  0.0000f,
                                                0.8090f, -0.5f, -0.5878f}, {0.2f, 0.2f, 0.0f});
    }
    else if (shape == DODECAHEDRON)
    {
        num_vertices = 108;
        scaling_factor = 0.7;
        float phi = 1.61803;

        generateTrianglesFromPolygon1(vertices, {-1, -1, 1,
                                                0, -1/phi, phi,
                                                1, -1, 1,
                                                1/phi, -phi, 0,
                                                -1/phi, -phi, 0}, {0.4f, 0.2f, 0.2f});

        generateTrianglesFromPolygon1(vertices, {-1/phi, -phi, 0,
                                                1/phi, -phi, 0,
                                                1, -1, -1,
                                                0, -1/phi, -phi,
                                                -1, -1, -1}, {0.5f, 0.5f, 0.5f});

        generateTrianglesFromPolygon1(vertices, {1, -1, 1,
                                                phi, 0, 1/phi,
                                                phi, 0, -1/phi,
                                                1, -1, -1,
                                                1/phi, -phi, 0}, {0.0f, 0.4f, 0.3f});

        generateTrianglesFromPolygon1(vertices, {1, -1, 1,
                                                0, -1/phi, phi,
                                                0, 1/phi, phi,
                                                1, 1, 1,
                                                phi, 0, 1/phi}, {0.6f, 0.1f, 0.0f});

        generateTrianglesFromPolygon1(vertices, {-1, 1, 1,
                                                0, 1/phi, phi,
                                                0, -1/phi, phi,
                                                -1, -1, 1,
                                                -phi, 0, 1/phi}, {0.5f, 0.0f, 0.5f});

        generateTrianglesFromPolygon1(vertices, {-1, -1, 1,
                                                -phi, 0, 1/phi,
                                                -phi, 0, -1/phi,
                                                -1, -1, -1,
                                                -1/phi, -phi, 0}, {0.0f, 0.5f, 0.5f});

        generateTrianglesFromPolygon1(vertices, {-phi, 0, 1/phi,
                                                -1, 1, 1,
                                                -1/phi, phi, 0,
                                                -1, 1, -1,
                                                -phi, 0, -1/phi}, {0.1f, 0.8f, 0.1f});

        generateTrianglesFromPolygon1(vertices, {-phi, 0, -1/phi,
                                                -1, 1, -1,
                                                0, 1/phi, -phi,
                                                0, -1/phi, -phi,
                                                -1, -1, -1}, {0.9f, 0.5f, 0.2f});

        generateTrianglesFromPolygon1(vertices, {0, 1/phi, -phi,
                                                1, 1, -1,
                                                phi, 0, -1/phi,
                                                1, -1, -1,
                                                0, -1/phi, -phi}, {0.2f, 0.2f, 0.6f});

        generateTrianglesFromPolygon1(vertices, {-1, 1, -1,
                                                -1/phi, phi, 0,
                                                1/phi, phi, 0,
                                                1, 1, -1,
                                                0, 1/phi, -phi}, {0.0f, 0.3f, 0.3f});

        generateTrianglesFromPolygon1(vertices, {-1, 1, 1,
                                                0, 1/phi, phi,
                                                1, 1, 1,
                                                1/phi, phi, 0,
                                                -1/phi, phi, 0}, {0.7f, 0.7f, 0.7f});

        generateTrianglesFromPolygon1(vertices, {1, 1, 1,
                                                phi, 0, 1/phi,
                                                phi, 0, -1/phi,
                                                1, 1, -1,
                                                1/phi, phi, 0}, {0.3f, 0.2f, 0.4f});
    }
    else if (shape == ICOSAHEDRON)
    {
        num_vertices = 60;
        scaling_factor = 0.7;
        float phi = 1.61803;

        generateTrianglesFromPolygon1(vertices, {-phi, -1, 0,
                                                0, -phi, 1,
                                                0, -phi, -1}, {0.3f, 0.2f, 0.4f});

        generateTrianglesFromPolygon1(vertices, {0, -phi, 1,
                                                phi, -1, 0,
                                                0, -phi, -1}, {0.5f, 0.5f, 0.5f});

        generateTrianglesFromPolygon1(vertices, {0, -phi, -1,
                                                phi, -1, 0,
                                                1, 0, -phi}, {0.4f, 0.0f, 0.7f});

        generateTrianglesFromPolygon1(vertices, {phi, -1, 0,
                                                phi, 1, 0,
                                                1, 0, phi}, {0.8f, 0.1f, 0.0f});

        generateTrianglesFromPolygon1(vertices, {1, 0, phi,
                                                phi, -1, 0,
                                                0, -phi, 1}, {0.3f, 1.0f, 0.0f});

        generateTrianglesFromPolygon1(vertices, {-1, 0, phi,
                                                1, 0, phi,
                                                0, -phi, 1}, {0.0f, 0.3f, 0.3f});

        generateTrianglesFromPolygon1(vertices, {0, -phi, 1,
                                                -phi, -1, 0,
                                                -1, 0, phi}, {0.7f, 0.2f, 0.4f});

        generateTrianglesFromPolygon1(vertices, {-1, 0, phi,
                                                0, phi, 1,
                                                1, 0, phi}, {0.2f, 0.5f, 0.8f});


        generateTrianglesFromPolygon1(vertices, {-phi, -1, 0,
                                                -1, 0, -phi,
                                                0, -phi, -1}, {0.4f, 0.4f, 0.6f});

        generateTrianglesFromPolygon1(vertices, {-1, 0, -phi,
                                                1, 0, -phi,
                                                0, -phi, -1}, {0.9f, 0.5f, 0.5f});

        generateTrianglesFromPolygon1(vertices, {-1, 0, -phi,
                                                1, 0, -phi,
                                                0, phi, -1}, {0.5f, 0.4f, 0.9f});

        generateTrianglesFromPolygon1(vertices, {-1, 0, -phi,
                                                -phi, 1, 0,
                                                0, phi, -1}, {0.6f, 0.6f, 0.3f});

        generateTrianglesFromPolygon1(vertices, {-1, 0, -phi,
                                                -phi, -1, 0,
                                                -phi, 1, 0}, {0.5f, 0.0f, 0.5f});

        generateTrianglesFromPolygon1(vertices, {-phi, -1, 0,
                                                -1, 0, phi,
                                                -phi, 1, 0}, {0.2f, 0.2f, 0.2f});

        generateTrianglesFromPolygon1(vertices, {-phi, 1, 0,
                                                -1, 0, phi,
                                                0, phi, 1}, {0.5f, 0.7f, 0.6f});

        generateTrianglesFromPolygon1(vertices, {0, phi, 1,
                                                0, phi, -1,
                                                -phi, 1, 0}, {0.1f, 0.3f, 0.1f});

        generateTrianglesFromPolygon1(vertices, {0, phi, -1,
                                                0, phi, 1,
                                                phi, 1, 0}, {0.8f, 0.8f, 0.8f});

        generateTrianglesFromPolygon1(vertices, {0, phi, -1,
                                                phi, 1, 0,
                                                1, 0, -phi}, {0.3f, 0.4f, 0.1f});

        generateTrianglesFromPolygon1(vertices, {0, phi, 1,
                                                1, 0, phi,
                                                phi, 1, 0}, {0.7f, 0.2f, 0.6f});

        generateTrianglesFromPolygon1(vertices, {1, 0, -phi,
                                                phi, -1, 0,
                                                phi, 1, 0}, {0.5f, 0.6f, 0.3f});
    }

    return {num_vertices, scaling_factor};
}

#endif
