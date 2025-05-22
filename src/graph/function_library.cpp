#include "function_library.hpp"
#include "core/constants.hpp"
#include <array> 
#include <random>

namespace FunctionLibrary
{

std::array<FunctionName, 5> functionNames{
    FunctionName::Wave,
    FunctionName::MultiWave,
    FunctionName::Ripple,
    FunctionName::Sphere,
    FunctionName::Torus
};

Function GetFunction(FunctionName name)
{
    static const std::vector<Function> functions{
        Wave, MultiWave, Ripple, Sphere, Torus
    };

    return functions[static_cast<int>(name)];
}

FunctionName GetNextFunctionName(FunctionName name)
{
    int next = (static_cast<int>(name) + 1) % functionNames.size();
    return static_cast<FunctionName>(next);
}

glm::mat4 Wave(glm::vec3 basePosition, float t, int resolution)
{
    glm::mat4 transform(1.0f);

    float yOffset{ sin(Constants::pi * (basePosition.x + basePosition.z + t)) };
    glm::vec3 position(basePosition.x, yOffset, basePosition.z);

    transform = glm::translate(transform, position);
    transform = glm::scale(transform, glm::vec3(2.0f / resolution));
    return transform;
}

glm::mat4 MultiWave(glm::vec3 basePosition, float t, int resolution)
{
    glm::mat4 transform(1.0f);

    float yOffset = sin(Constants::pi * (basePosition.x + 0.5f * t));
    yOffset += 0.5f * sin(2.0f * Constants::pi * (basePosition.z + t));
    yOffset += sin(Constants::pi * (basePosition.x + basePosition.z + 0.25f * t));
    yOffset *= 1.0f / 2.5f;
    glm::vec3 position(basePosition.x, yOffset, basePosition.z);


    transform = glm::translate(transform, position);
    transform = glm::scale(transform, glm::vec3(2.0f / resolution));
    return transform;
}

glm::mat4 Ripple(glm::vec3 basePosition, float t, int resolution)
{
    glm::mat4 transform(1.0f);

    float d = sqrt(basePosition.x * basePosition.x + basePosition.z * basePosition.z);
    float yOffset = sin(Constants::pi * (4.0f * d - t));
    yOffset /= 1.0f + 10.0f * d;
    glm::vec3 position(basePosition.x, yOffset, basePosition.z);

    transform = glm::translate(transform, position);
    transform = glm::scale(transform, glm::vec3(2.0f / resolution));
    return transform;
}

glm::mat4 Sphere(glm::vec3 basePosition, float t, int resolution)
{
    glm::mat4 transform(1.0f);

    float r = 0.9f + 0.1f * sin(Constants::pi * (6.0f * basePosition.x + 4.0f * basePosition.z + t));
    float s = r * cos(0.5f * Constants::pi * basePosition.z);
    glm::vec3 position{};
    position.x = s * sin(Constants::pi * basePosition.x);
    position.y = r * sin(0.5f * Constants::pi * basePosition.z);
    position.z = s * cos(Constants::pi * basePosition.x);
    
    transform = glm::translate(transform, position);
    transform = glm::scale(transform, glm::vec3(2.0f / resolution));
    return transform;
}

glm::mat4 Torus(glm::vec3 basePosition, float t, int resolution)
{
    glm::mat4 transform(1.0f);

    float r1 = 0.7f + 0.1f * sin(Constants::pi * (6.0f * basePosition.x + 0.5f * t));
    float r2 = 0.15f + 0.05f * sin(Constants::pi * (8.0f * basePosition.x + 4.0f * basePosition.z + 2.0f * t));
    float s = r1 + r2 * cos(Constants::pi * basePosition.z);
    glm::vec3 position{};
    position.x = s * sin(Constants::pi * basePosition.x);
    position.y = r2 * sin(Constants::pi * basePosition.z);
    position.z = s * cos(Constants::pi * basePosition.x);

    transform = glm::translate(transform, position);
    transform = glm::scale(transform, glm::vec3(2.0f / resolution));
    return transform;
}

// TODO: move GetRandom functions to Graph
FunctionName GetRandomFunctionName() {
    static std::random_device rd{};
    static std::mt19937 mt{ rd() };
    static std::uniform_int_distribution<int> rand{
      0, static_cast<int>(functionNames.size() - 1)
    };

    return static_cast<FunctionName>(rand(mt));
}

FunctionName GetRandomFunctionNameOtherThan(FunctionName name) {
    static std::random_device rd{};
    static std::mt19937 mt{ rd() };

    // It is very important to recalculate this range every time so it
    // properly excludes "name"
    size_t num_function_names = functionNames.size();
    std::uniform_int_distribution<int> rand{ 0,
                                            static_cast<int>(num_function_names - 1) };

    FunctionName choice;
    do {
        // This can be slow and inefficient. Ensure FunctionName is small.
        choice = static_cast<FunctionName>(rand(mt));
    } while (choice == name);

    return choice;
}

// TODO: add interpolation and transitioning between functions

}  // namespace FunctionLibrary
