#pragma once

#include "core/gl_includes.hpp"

#include <glm/glm.hpp>

#include "engine/camera/camera.hpp"
#include "gui/gui.hpp"

class Renderer
{
public:
	Renderer()  = default;
	~Renderer() = default;

	void init();
	void render(const Camera& camera, float deltaTime);

private:
	// Add renderable objects, shaders, etc. as needed
	void clearScreen() const;
};