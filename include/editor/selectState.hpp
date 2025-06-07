#pragma once

#include "editor/state.hpp"

class SelectState : public State
{
public:
    SelectState(Editor* editor);

    void input(GLFWwindow* window) override;
};