#pragma once

#include "core/gl_includes.hpp"

#include <string>

class Texture {
public:
    // Load and create a texture from file
    explicit Texture(const std::string& path);
    ~Texture();

    void bind(GLuint unit = 0) const;
    GLuint id() const { return textureID; }

private:
    GLuint textureID;
    int width, height, channels;
};
