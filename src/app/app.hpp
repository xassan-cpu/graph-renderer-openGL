#pragma once
#include "core/gl_includes.hpp"
#include "renderer/renderer.hpp"
#include "gui/gui.hpp"
#include "engine/camera/camera.hpp"
#include "core/constants.hpp"
#include <memory>

class App
{
public:
    App(int width = Constants::screen_width,
        int height = Constants::screen_height,
        const char* title = "Graph Renderer");
    ~App();

    void run();

private:
    unsigned int width;
    unsigned int height;
    const char* title;

    GLFWwindow* window;
    std::unique_ptr<Gui> gui;
    Renderer renderer;
    Camera camera;

    void init();
    void processInput(float deltaTime);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};