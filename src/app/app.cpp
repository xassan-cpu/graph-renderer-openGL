#include "app.hpp"
#include "core/gl_utils/gl_utils.hpp"
#include <iostream>

App::App(int width, int height, const char* title)
    : width(width), height(height), title(title),
      renderer{}, camera{ glm::vec3(0.0f, 0.0f, 3.0f) }
{
    init();
}

App::~App()
{
    glfwTerminate();
}

void App::init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window =
        glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        std::exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetWindowUserPointer(window, this);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        std::exit(EXIT_FAILURE);
    }

    renderer.init();
    gui = std::make_unique<Gui>(window);
}

void App::run()
{
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(deltaTime);

        gui->beginFrame();

        renderer.render(camera, deltaTime);

        gui->endFrame();

        glfwSwapBuffers(window);
        glfwPollEvents();
        glCheckError();
    }
}

void App::processInput(float deltaTime)
{
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

void App::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void App::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));

    static float lastX = Constants::screen_width / 2.0f;
    static float lastY = Constants::screen_height / 2.0f;
    static bool firstMouse = true;

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    if (app)
    {
        app->camera.processMouseMovement(xoffset, yoffset);
    }
}

void App::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    App* app = static_cast<App*>(glfwGetWindowUserPointer(window));
    if (app)
    {
        app->camera.processMouseScroll(static_cast<float>(yoffset));
    }
}