#include "ifcg/shader/vbo.hpp"

namespace vbo
{
    VBO::VBO(const std::vector<Vertex>& vertices)
    {
        glGenBuffers(1, &_id);
        bind();
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
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