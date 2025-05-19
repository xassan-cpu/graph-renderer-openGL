#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.hpp"
#include "gl_utils.hpp"
#include "constants.hpp"
#include "gui.hpp"

#include <iostream>
#include <array>
#include <vector>

// ---------------------------------------------------------------------------------------------
// GLFW Callback Functions
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window, Camera& camera, float deltaTime);

// ---------------------------------------------------------------------------------------------
// Main Function
// ---------------------------------------------------------------------------------------------
int main()
{
    // -----------------------------------------------------------------------------------------
    // GLFW + OpenGL Context Setup
    // -----------------------------------------------------------------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window =
        glfwCreateWindow(Constants::screen_width, Constants::screen_height, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Capture mouse input, disabling cursor
    /*glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);*/

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    // -----------------------------------------------------------------------------------------
    // Camera and Input Setup
    // -----------------------------------------------------------------------------------------
    Camera camera{ glm::vec3(0.0f, 0.0f, 3.0f) };

    // Pass the camera to callback functions via window user pointer
    glfwSetWindowUserPointer(window, &camera);

    // -----------------------------------------------------------------------------------------
    // ImGui Setup
    // -----------------------------------------------------------------------------------------
    Gui gui(window);

    // -----------------------------------------------------------------------------------------
    // OpenGL State
    // -----------------------------------------------------------------------------------------
    glEnable(GL_DEPTH_TEST);

    // -----------------------------------------------------------------------------------------
    // Main Render Loop
    // -----------------------------------------------------------------------------------------
    float deltaTime{ 0.0f }, lastFrame{ 0.0f };

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame{ static_cast<float>(glfwGetTime()) };
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window, camera, deltaTime);

        gui.beginFrame();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        gui.endFrame();

        glfwSwapBuffers(window);
        glfwPollEvents();
        glCheckError();
    }

    // -----------------------------------------------------------------------------------------
    // Cleanup
    // -----------------------------------------------------------------------------------------

    glfwTerminate();
    return 0;
}

// GLFW: Callback function for framebuffer size changes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// GLFW: Callback function for mouse movement
void processInput(GLFWwindow* window, Camera& camera, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(CameraMovement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(CameraMovement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(CameraMovement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(CameraMovement::RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    static float lastX{ Constants::screen_width / 2.0f };
    static float lastY{ Constants::screen_height / 2.0f };
    static bool firstMouse{ true };

    float xpos{ static_cast<float>(xposIn) };
    float ypos{ static_cast<float>(yposIn) };

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset{ xpos - lastX };
    float yoffset{ lastY - ypos };
    lastX = xpos;
    lastY = ypos;

    Camera* camera{
        static_cast<Camera*>(glfwGetWindowUserPointer(window)) };
    if (camera) {
        camera->processMouseMovement(xoffset, yoffset);
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    Camera* camera{
        static_cast<Camera*>(glfwGetWindowUserPointer(window)) };
    if (camera) {
        camera->processMouseScroll(static_cast<float>(yoffset));
    }
}