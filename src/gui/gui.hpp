#pragma once

#include "core/gl_includes.hpp"

class Gui {
public:
    Gui(GLFWwindow* window);
    ~Gui();

    void beginFrame();
    void endFrame();

private:
    void showDemoPanel();

    GLFWwindow* window;
};
