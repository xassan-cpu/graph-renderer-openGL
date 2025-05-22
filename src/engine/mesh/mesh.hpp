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

    std::vector<Vertex> getVertices() const;

    void draw() const;
    void drawInstanced(GLsizei instanceCount) const;
    void setInstanceTransforms(const std::vector<glm::mat4>& transforms);

private:
    GLuint VAO, VBO;
    GLuint instanceVBO = 0;
    GLsizei vertexCount;
    GLuint instanceVBOs[2] = { 0, 0 };
    int currentInstanceVBO = 0;
    bool instancingEnabled = false;

    void setupMesh(const std::vector<Vertex>& vertices, bool withNormals, bool withTexCoords);
    std::vector<Vertex> vertices;
};
