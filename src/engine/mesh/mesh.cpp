#include "mesh.hpp"
#include "core/gl_utils/gl_utils.hpp"

Mesh::Mesh(const std::vector<Vertex>& vertices, bool withNormals, bool withTexCoords)
    : vertices(vertices)
{
    setupMesh(vertices, withNormals, withTexCoords);
}

void Mesh::setupMesh(const std::vector<Vertex>& vertices, bool withNormals, bool withTexCoords)
{
    vertexCount = static_cast<GLsizei>(vertices.size());

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glCheckError();

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glCheckError();

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(),
        GL_DYNAMIC_DRAW);
    glCheckError();

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glCheckError();

    // Normal attribute
    if (withNormals)
    {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            (void*)offsetof(Vertex, normal));
        glEnableVertexAttribArray(1);
        glCheckError();
    }

    // Texture coord attribute
    if (withTexCoords)
    {
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
            (void*)offsetof(Vertex, texCoords));
        glEnableVertexAttribArray(2);
        glCheckError();
    }

    // Unbind VAO
    glBindVertexArray(0);
}

void Mesh::setInstanceTransforms(const std::vector<glm::mat4>& transforms)
{
    // Double-buffered instance VBOs - Alternating between VBOs
    if (instanceVBOs[0] == 0)
        glGenBuffers(2, instanceVBOs);

    currentInstanceVBO = (currentInstanceVBO + 1) % 2;
    GLuint activeVBO = instanceVBOs[currentInstanceVBO];

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, activeVBO);
    //glBufferData(GL_ARRAY_BUFFER, transforms.size() * sizeof(glm::mat4), transforms.data(), GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, transforms.size() * sizeof(glm::mat4), nullptr, GL_DYNAMIC_DRAW); // Orphan
    glBufferSubData(GL_ARRAY_BUFFER, 0, transforms.size() * sizeof(glm::mat4), transforms.data());

    // Setup 4 attributes (locations 1,2,3,4) for mat4
    for (GLuint i = 0; i < 4; ++i)
    {
        glEnableVertexAttribArray(1 + i);
        glVertexAttribPointer(1 + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(float) * i * 4));
        glVertexAttribDivisor(1 + i, 1);
    }

    glBindVertexArray(0);
    instancingEnabled = true;
}

void Mesh::drawInstanced(GLsizei instanceCount) const
{
    if (!instancingEnabled)
    {
        draw();
        return;
    }
    //std::cout << "gpu instancing" << '\n';
    glBindVertexArray(VAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, vertexCount, instanceCount);
    glBindVertexArray(0);
}


std::vector<Vertex> Mesh::getVertices() const {
    return vertices;
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Mesh::draw() const {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}