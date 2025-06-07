#include "editor/editor.hpp"

Editor::Editor() 
    : currentMesh(nullptr), meshes(&IFCG::renderQueue), selectState(this), editorState(this), currentState(&selectState) {}

bool Editor::isKeyJustPressed(GLFWwindow* window, int key) {
    int currentState = glfwGetKey(window, key);
    bool justPressed = false;

    if (currentState == GLFW_PRESS && keyStates[key] == GLFW_RELEASE) {
        justPressed = true;
    }

    keyStates[key] = currentState;
    return justPressed;
};

void Editor::changeState()
{
    if (currentState == &selectState) {
        currentState = &editorState;
    } else {
        currentState = &selectState;
    }
};

void Editor::input(GLFWwindow* window) {
    currentState->input(window);

    if (isKeyJustPressed(window, GLFW_KEY_C))
    {
        IFCG::addMesh(new Cube3D(IFCG::shader.id));
    }
};