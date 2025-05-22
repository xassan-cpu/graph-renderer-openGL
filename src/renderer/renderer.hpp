#pragma once
#include "core/gl_includes.hpp"
#include <glm/glm.hpp>
#include "engine/camera/camera.hpp"
#include "graph/graph.hpp"
#include "core/shader/shader.hpp"
#include <memory>

class Renderer
{
public:
	Renderer()  = default;
	~Renderer() = default;

	void init();
	void render(const Camera& camera, float deltaTime);

private:
	// Add renderable objects, shaders, etc. as needed
	std::shared_ptr<Shader> shader;
	std::unique_ptr<Graph> graph;

	void clearScreen() const;
};