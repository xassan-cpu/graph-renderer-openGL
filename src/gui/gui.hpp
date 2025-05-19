#pragma once

#include "core/gl_includes.hpp"

class Gui {
public:
    Gui(GLFWwindow* window);
    ~Gui();

    void beginFrame();  // Starts ImGui frame
    void endFrame();    // Renders ImGui draw data

private:
    void showDemoPanel();

    GLFWwindow* window;
};
