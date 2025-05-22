#include "graph.hpp"
#include "engine/mesh_utils/meshutils.hpp"

Graph::Graph(FunctionLibrary::FunctionName functionName, int resolution)
    : functionName(functionName), resolution(resolution),
      function(FunctionLibrary::GetFunction(functionName))
{
    float duration{};
    step = 2.0f / resolution;

    positions.resize(resolution * resolution);
    mesh = std::make_shared<Mesh>(createCubeVertices(), false, false);

    for (std::size_t i = 0, x = 0, z = 0; i < resolution * resolution; ++i, ++x)
    {
        if (x == resolution) {
            x = 0;
            ++z;
        }

        float u{ (x + 0.5f) * step - 1.0f };
        float v{ (z + 0.5f) * step - 1.0f };

        positions[i] = glm::vec3(u, 0.0f, v);
    }
}

void Graph::update(float deltaTime)
{
    duration += deltaTime;

    if (duration >= functionDuration)
    {
        duration -= functionDuration;

        functionName = FunctionLibrary::GetNextFunctionName(functionName);
        function = FunctionLibrary::GetFunction(functionName);
    }
}

glm::mat4 Graph::getModelMatrix(std::size_t index, float time) const
{
    
    return function(positions[index], time, resolution);
}

Mesh& Graph::getMesh()
{
    return *mesh;
}

int Graph::getPointCount() const
{
    return static_cast<int>(positions.size());
}

std::vector<glm::mat4> Graph::getAllModelMatrices(float time) const
{
    std::vector<glm::mat4> models(positions.size());
    for (std::size_t i = 0; i < positions.size(); ++i)
    {
        models[i] = getModelMatrix(i, time);
    }
    return models;
}
