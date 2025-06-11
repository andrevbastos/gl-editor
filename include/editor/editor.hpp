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
    void castRay();
    
    Mesh* currentMesh;
    Vertex* currentVertex;
    std::vector<Mesh*>* meshes;
    
private:
    std::map<int, int> keyStates;
    
    SelectState selectState;
    EditorState editorState;
    State* currentState;
    
    Vertex* checkRayCol(glm::vec3 ray_origin, glm::vec3 ray_end, glm::mat4 view, glm::mat4 projection);
    void makeLine(glm::vec3 near, glm::vec3 far);
};