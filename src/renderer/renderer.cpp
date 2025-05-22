#include "renderer.hpp"

void Renderer::init()
{
	// Initialize OpenGL state
	glEnable(GL_DEPTH_TEST);

    int resolution{ 100 };

    shader = std::make_shared<Shader>("shaders/basic.vert.glsl", "shaders/basic.frag.glsl");
    graph = std::make_unique<Graph>(FunctionLibrary::FunctionName::Sphere, resolution);
}

void Renderer::clearScreen() const
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // dark background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(const Camera& camera, float deltaTime)
{
    // Update function cycling
    graph->update(deltaTime);

    clearScreen();

    // Get dynamic window size
    int width, height;
    glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);
    float aspect = static_cast<float>(width) / static_cast<float>(height);

    // --- Draw Scene Here ---
    // Use shaders, bind VAOs, set uniforms like view/projection...

    glm::mat4 view{ camera.getViewMatrix() };
    glm::mat4 projection{ camera.getProjectionMatrix(aspect) };

    shader->use();
    shader->setMat4("u_view", view);
    shader->setMat4("u_projection", projection);

    const Mesh& mesh{ graph->getMesh() };
    int count{ graph->getPointCount() };

    // CPU Instancing
    for (std::size_t i = 0; i < count; ++i)
    {
        glm::mat4 model = graph->getModelMatrix(i, glfwGetTime());
        shader->setMat4("u_model", model);
        mesh.draw();
    }

    // GPU Instancing
    /*std::vector<glm::mat4> modelMatrices = graph->getAllModelMatrices(glfwGetTime());
    graph->getMesh().setInstanceTransforms(modelMatrices);
    graph->getMesh().drawInstanced(modelMatrices.size());*/
}