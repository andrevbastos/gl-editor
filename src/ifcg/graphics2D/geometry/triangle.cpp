#include "ifcg/graphics2D/geometry/triangle.hpp"

namespace mesh2D
{
    Triangle2D::Triangle2D(GLuint shaderID)
        : Mesh2D(
        {
            Vertex2D{  1.0f, -0.866f, 1.0f, 0.0f, 0.0f, 1.0f },
            Vertex2D{ -1.0f, -0.866f, 0.0f, 1.0f, 0.0f, 1.0f },
            Vertex2D{  0.0f,  0.866f, 0.0f, 0.0f, 1.0f, 1.0f }
        },
        {
            0, 1, 2
        },
        shaderID
    ) {}
};
