#pragma once

#include "ifcg/ifcg.hpp"
#include <vector>
#include <map>
#include <GLFW/glfw3.h>
#include "ifcg/graphics3D/geometry/cube.hpp"
#include "editor/state.hpp"
#include "editor/editorState.hpp"
#include "editor/selectState.hpp"

class Editor {
public:
    Editor();
    void input(GLFWwindow* window);
    void changeState();
    bool isKeyJustPressed(GLFWwindow* window, int key);

    // Membros públicos para que os estados possam acessá-los
    Mesh* currentMesh;
    std::vector<Mesh*>* meshes;

private:
    std::map<int, int> keyStates;
    
    SelectState selectState;
    EditorState editorState;
    State* currentState;
};