#pragma once

#include <GLFW/glfw3.h>

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
