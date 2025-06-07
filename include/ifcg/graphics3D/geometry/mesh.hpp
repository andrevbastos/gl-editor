#pragma once

#include "ifcg/common/mesh.hpp"

namespace mesh3D
{
    class Mesh3D : public ifcg::Mesh
    {
    public:
        virtual ~Mesh3D() = default;
        Mesh3D(std::vector<Vertex3D> vertices, std::vector<GLuint> indices, GLuint shaderID);
	    Mesh3D(const std::vector<Mesh3D*>& meshes, GLuint shaderID);

        virtual void draw(glm::mat4 m);
        virtual void drawOutline();
        
        virtual void translate(float tX, float tY, float tZ);
        virtual void scale(float sX, float sY, float sZ);
        virtual void rotate(float angle, float rX, float rY, float rZ);
        virtual void reflect(bool refX, bool refY, bool refZ);

        virtual void setOutline(bool outline);

    private:
        std::vector<Vertex3D> vertices;
        std::vector<GLuint> indices;

        GLuint shaderID;
        VAO vao;
        
		glm::mat4 model = glm::mat4(1.0f);
		std::vector<Mesh3D*> subMeshes;

        bool outline = false;
    };
};

using namespace mesh3D;