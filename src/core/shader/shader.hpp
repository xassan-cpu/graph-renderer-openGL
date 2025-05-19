#pragma once
#include "core/gl_includes.hpp"

#include <glm/glm.hpp>

#include <string>
#include <string_view>

class Shader
{
public:
        unsigned int ID;  // OpenGL shader program ID

        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader();

        // Activates the shader program
        void use() const;

        // Utility uniform functions
        void setBool(const std::string_view name, bool value) const;
        void setInt(const std::string_view name, int value) const;
        void setFloat(const std::string_view name, float value) const;
        void setVec2(const std::string_view name, const glm::vec2& value) const;
        void setVec2(const std::string_view name, float x, float y) const;
        void setVec3(const std::string_view name, const glm::vec3& value) const;
        void setVec3(const std::string_view name, float x, float y, float z) const;
        void setVec4(const std::string_view name, const glm::vec4& value) const;
        void setVec4(const std::string_view name, float x, float y, float z, float w) const;
        void setMat2(const std::string_view name, const glm::mat2& mat) const;
        void setMat3(const std::string_view name, const glm::mat3& mat) const;
        void setMat4(const std::string_view name, const glm::mat4& mat) const;

private:
        void checkCompileErrors(unsigned int shader, const std::string& type);
};
