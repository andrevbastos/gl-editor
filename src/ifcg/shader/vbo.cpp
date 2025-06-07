#include "ifcg/shader/vbo.hpp"

namespace vbo
{
    VBO::VBO(const std::vector<Vertex2D>& vertices)
    {
        glGenBuffers(1, &_id);
        bind();
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex2D), vertices.data(), GL_STATIC_DRAW);
    }

    VBO::VBO(const std::vector<Vertex3D>& vertices)
    {
        glGenBuffers(1, &_id);
        bind();
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex3D), vertices.data(), GL_STATIC_DRAW);
    }

    void VBO::bind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, _id);
    }

    void VBO::unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VBO::destroy()
    {
        glDeleteBuffers(1, &_id);
    }
}