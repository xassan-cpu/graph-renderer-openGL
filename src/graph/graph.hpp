#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "function_library.hpp"
#include "engine/mesh/mesh.hpp"
#include "core/shader/shader.hpp"
#include <memory>

// TODO: add configuration option for the transition mode
enum class TransitionMode{ Cycle, Random };

class Graph
{
public:
    Graph(FunctionLibrary::FunctionName functionName, int resolution);
    ~Graph() = default;

    glm::mat4 getModelMatrix(std::size_t index, float time) const;
    std::vector<glm::mat4> getAllModelMatrices(float time) const;
    Mesh& getMesh();
    int getPointCount() const;
    void update(float deltaTime);


private:
    FunctionLibrary::FunctionName functionName;
    FunctionLibrary::Function function;

    std::vector<glm::vec3> positions;
    std::shared_ptr<Mesh> mesh;

    int resolution;
    float step;
    float duration = 0.0f;
    float functionDuration = 1.0f;
};