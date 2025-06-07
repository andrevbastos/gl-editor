#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "editor/editor.hpp"
#include "ifcg/ifcg.hpp"
#include "ifcg/common/mesh.hpp"

unsigned int width = 800;
unsigned int height = 600;

int main()
{
    IFCG::init();
    IFCG::createWindow(width, height);

    IFCG::setup3D();

    Editor editor;
    // Placeholder for mesh, replace with actual mesh creation
    // IFCG::addMesh(new Mesh()); 

    while (!IFCG::shouldClose())
    {
        IFCG::readInputs();
        IFCG::processInput();
        IFCG::clearBuffer(1.0f, 1.0f, 1.0f, 1.0f);
        
        editor.input(IFCG::window);

        IFCG::render();
        
        IFCG::swapBuffer();
    }

    IFCG::terminate();
    return 0;
}