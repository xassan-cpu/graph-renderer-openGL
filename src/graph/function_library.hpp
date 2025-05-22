#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <functional>
#include <array> 


namespace FunctionLibrary
{
using Function = std::function<glm::mat4(glm::vec3, float, int)>;

enum class FunctionName { Wave, MultiWave, Ripple, Sphere, Torus };

glm::mat4 Wave(glm::vec3 basePosition, float t, int resolution);
glm::mat4 MultiWave(glm::vec3 basePosition, float t, int resolution);
glm::mat4 Ripple(glm::vec3 basePosition, float t, int resolution);
glm::mat4 Sphere(glm::vec3 basePosition, float t, int resolution);
glm::mat4 Torus(glm::vec3 basePosition, float t, int resolution);

Function GetFunction(FunctionName name);
FunctionName GetNextFunctionName(FunctionName name);
FunctionName GetRandomFunctionName();
FunctionName GetRandomFunctionNameOtherThan(FunctionName name);

}  // namespace FunctionLibrary