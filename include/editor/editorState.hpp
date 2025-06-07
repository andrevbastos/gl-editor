#pragma once

#include "editor/state.hpp"

class EditorState : public State
{
public:
    EditorState(Editor* editor);

    void input(GLFWwindow* window) override;
};