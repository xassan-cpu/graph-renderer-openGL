#pragma once

#include "core/gl_includes.hpp"
#include <glm/glm.hpp>

#include <vector>


struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, bool withNormals = true, bool withTexCoords = true);
    ~Mesh();

    void draw() const;

private:
    GLuint VAO, VBO;
    GLsizei vertexCount;
};
