#include "renderer.hpp"

void Renderer::init()
{
	// Initialize OpenGL state
	glEnable(GL_DEPTH_TEST);
}

void Renderer::clearScreen() const {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // dark background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render(const Camera& camera, float deltaTime)
{
    clearScreen();

    // --- Draw Scene Here ---
    // Use shaders, bind VAOs, set uniforms like view/projection...

    
}