#include <glad/glad.h>
#include "mesh.hpp"
#include "gl_utils.hpp"

Mesh::Mesh(const std::vector<Vertex>& vertices, bool withNormals, bool withTexCoords)
{
    vertexCount = static_cast<GLsizei>(vertices.size());

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glCheckError();

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glCheckError();

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(),
        GL_STATIC_DRAW);
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

Mesh::~Mesh() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Mesh::draw() const {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0);
}