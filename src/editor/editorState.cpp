#include "editor/editor.hpp"
#include "editor/editorState.hpp"

EditorState::EditorState(Editor* editor) : State(editor) {}

void EditorState::input(GLFWwindow* window) {
    if (editor->isKeyJustPressed(window, GLFW_KEY_ENTER)) {
        editor->changeState();
    }

    if (!editor->currentMesh) {
        return;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)
    {
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            editor->currentMesh->rotate(0.05f, 1.0f, 0.0f, 0.0f);
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            editor->currentMesh->rotate(0.05f, -1.0f, 0.0f, 0.0f);
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            editor->currentMesh->rotate(0.05f, 0.0f, 1.0f, 0.0f);
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            editor->currentMesh->rotate(0.05f, 0.0f, -1.0f, 0.0f);
        }
        if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS)
        {
            editor->currentMesh->rotate(0.05f, 0.0f, 0.0f, 1.0f);
        }
        if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS)
        {
            editor->currentMesh->rotate(0.05f, 0.0f, 0.0f, -1.0f);
        }
    } else 
    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS)
    {
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            editor->currentMesh->scale(1.1f, 1.0f, 1.0f);
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            editor->currentMesh->scale(0.9f, 1.0f, 1.0f);
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            editor->currentMesh->scale(1.0f, 1.1f, 1.0f);
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            editor->currentMesh->scale(1.0f, 0.9f, 1.0f);
        }
        if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS)
        {
            editor->currentMesh->scale(1.0f, 1.0f, 1.1f);
        }
        if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS)
        {
            editor->currentMesh->scale(1.0f, 1.0f, 0.9f);
        }
    } else{
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            editor->currentMesh->translate(0.1f, 0.0f, 0.0f);
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            editor->currentMesh->translate(-0.1f, 0.0f, 0.0f);
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            editor->currentMesh->translate(0.0f, 0.1f, 0.0f);
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            editor->currentMesh->translate(0.0f, -0.1f, 0.0f);
        }
        if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS)
        {
            editor->currentMesh->translate(0.0f, 0.0f, 0.1f);
        }
        if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS)
        {
            editor->currentMesh->translate(0.0f, 0.0f, -0.1f);
        }
    }
}