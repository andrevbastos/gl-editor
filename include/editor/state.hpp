#pragma once

class Editor;
#include <GLFW/glfw3.h>

class State
{
public:
    State(Editor* editor) : editor(editor) {}
    virtual ~State() = default;

    virtual void input(GLFWwindow* window) = 0;
protected:
    Editor* editor;
};