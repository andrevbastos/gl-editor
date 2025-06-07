#include "editor/editor.hpp"
#include "editor/selectState.hpp"

SelectState::SelectState(Editor* editor) : State(editor) {}

void SelectState::input(GLFWwindow* window) {
    if (editor->isKeyJustPressed(window, GLFW_KEY_ENTER)) {
        editor->changeState();
    }
    if (editor->isKeyJustPressed(window, GLFW_KEY_LEFT))
    {
        if (editor->currentMesh != nullptr) {
            auto meshIndex = std::find(editor->meshes->begin(), editor->meshes->end(), editor->currentMesh);
            if (meshIndex != editor->meshes->end() && meshIndex != editor->meshes->begin()) {
                editor->currentMesh->setOutline(false);
                --meshIndex;
                editor->currentMesh = *meshIndex;
                editor->currentMesh->setOutline(true);
            } else {
                editor->currentMesh->setOutline(false);
                editor->currentMesh = editor->meshes->back();
                editor->currentMesh->setOutline(true);
            }
        } else if (!editor->meshes->empty()) {
            editor->currentMesh = editor->meshes->back();
            editor->currentMesh->setOutline(true);
        }
    }
    if (editor->isKeyJustPressed(window, GLFW_KEY_RIGHT))
    {
        if (editor->currentMesh != nullptr) {
            auto meshIndex = std::find(editor->meshes->begin(), editor->meshes->end(), editor->currentMesh);
            if (meshIndex != editor->meshes->end() && meshIndex != editor->meshes->end() - 1) {
                editor->currentMesh->setOutline(false);
                ++meshIndex;
                editor->currentMesh = *meshIndex;
                editor->currentMesh->setOutline(true);
            } else {
                editor->currentMesh->setOutline(false);
                editor->currentMesh = editor->meshes->front();
                editor->currentMesh->setOutline(true);
            }
        } else if (!editor->meshes->empty()) {
            editor->currentMesh = editor->meshes->front();
            editor->currentMesh->setOutline(true);
        }
    }
}