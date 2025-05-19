#include "shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

static std::string readFile(const std::string& path)
{
        std::ifstream file(path);
        if (!file.is_open())
                throw std::runtime_error("Failed to open file " + path);

        std::ostringstream ss;
        ss << file.rdbuf();
        return ss.str();
}

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
        std::string vertexCode;
        std::string fragmentCode;

        try
        {
                vertexCode = readFile(vertexPath);
                fragmentCode = readFile(fragmentPath);
        }
        catch (const std::exception& e)
        {
                std::cerr << "ERROR::SHADER::FILE_NOT_READ: " << e.what() << '\n';
                std::exit(EXIT_FAILURE);
        }

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        unsigned int vertex, fragment;

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, nullptr);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, nullptr);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");

        //Shader program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(fragment);
}

Shader::~Shader() { glDeleteProgram(ID); }

void Shader::use() const { glUseProgram(ID); }

void Shader::setBool(const std::string_view name, bool value) const
{
        glUniform1i(glGetUniformLocation(ID, name.data()),
                                static_cast<int>(value));
}

void Shader::setInt(const std::string_view name, int value) const
{
        glUniform1i(glGetUniformLocation(ID, name.data()), value);
}

void Shader::setFloat(const std::string_view name, float value) const
{
        glUniform1f(glGetUniformLocation(ID, name.data()), value);
}

void Shader::setVec2(const std::string_view name, const glm::vec2& value) const
{
        glUniform2fv(glGetUniformLocation(ID, name.data()), 1, &value[0]);
}

void Shader::setVec2(const std::string_view name, float x, float y) const
{
        glUniform2f(glGetUniformLocation(ID, name.data()), x, y);
}

void Shader::setVec3(const std::string_view name, const glm::vec3& value) const
{
        glUniform3fv(glGetUniformLocation(ID, name.data()), 1, &value[0]);
}

void Shader::setVec3(const std::string_view name, float x, float y, float z) const
{
        glUniform3f(glGetUniformLocation(ID, name.data()), x, y, z);
}

void Shader::setVec4(const std::string_view name, const glm::vec4& value) const
{
        glUniform4fv(glGetUniformLocation(ID, name.data()), 1, &value[0]);
}

void Shader::setVec4(const std::string_view name, float x, float y, float z,
                                         float w) const
{
        glUniform4f(glGetUniformLocation(ID, name.data()), x, y, z, w);
}

void Shader::setMat2(const std::string_view name, const glm::mat2& mat) const
{
        glUniformMatrix2fv(glGetUniformLocation(ID, name.data()), 1, GL_FALSE,
                                           &mat[0][0]);
}

void Shader::setMat3(const std::string_view name, const glm::mat3& mat) const
{
        glUniformMatrix3fv(glGetUniformLocation(ID, name.data()), 1, GL_FALSE,
                               &mat[0][0]);
}

void Shader::setMat4(const std::string_view name, const glm::mat4& mat) const
{
        glUniformMatrix4fv(glGetUniformLocation(ID, name.data()), 1, GL_FALSE,
                               &mat[0][0]);
}

void Shader::checkCompileErrors(unsigned int shader, const std::string& type)
{
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if (!success)
                {
                        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                        std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- \n";
                }
        }
        else
        {
                glGetProgramiv(shader, GL_LINK_STATUS, &success);
                if (!success)
                {
                        glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                        std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- \n";
                }
        }
}
