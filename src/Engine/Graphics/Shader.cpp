#include "Shader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cctype>
#include <unordered_map>

#include "glad/gl.h"
#include "glm/fwd.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace {
    std::string LTrim(const std::string &value) {
        std::size_t index = 0;
        while (index < value.size() && std::isspace(static_cast<unsigned char>(value[index])) != 0) {
            ++index;
        }
        return value.substr(index);
    }

    std::string StripUtf8Bom(const std::string &value) {
        if (value.size() >= 3 &&
            static_cast<unsigned char>(value[0]) == 0xEF &&
            static_cast<unsigned char>(value[1]) == 0xBB &&
            static_cast<unsigned char>(value[2]) == 0xBF) {
            return value.substr(3);
        }
        return value;
    }

    std::string ToLower(std::string value) {
        for (char &ch: value) {
            ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        }
        return value;
    }

    std::unordered_map<std::string, std::string> ParseShaderStages(const std::string &shaderSource) {
        std::unordered_map<std::string, std::string> shaderStages;

        std::istringstream sourceStream(shaderSource);
        std::string line;
        std::string currentStage;
        std::stringstream currentStageSource;

        auto FlushStage = [&]() {
            if (!currentStage.empty()) {
                shaderStages[currentStage] = currentStageSource.str();
                currentStageSource.str("");
                currentStageSource.clear();
            }
        };

        while (std::getline(sourceStream, line)) {
            std::string normalizedLine = StripUtf8Bom(line);
            normalizedLine = LTrim(normalizedLine);
            if (normalizedLine.rfind("#type", 0) == 0) {
                FlushStage();

                std::istringstream typeStream(normalizedLine);
                std::string typeToken;
                typeStream >> typeToken >> currentStage;
                currentStage = ToLower(currentStage);
                continue;
            }

            if (!currentStage.empty()) {
                currentStageSource << line << '\n';
            }
        }

        FlushStage();
        return shaderStages;
    }

    bool CompileStage(unsigned int shaderId, const char *shaderCode, const char *stageName) {
        int success = 0;
        char infoLog[1024] = {0};

        glShaderSource(shaderId, 1, &shaderCode, nullptr);
        glCompileShader(shaderId);
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shaderId, 1024, nullptr, infoLog);
            std::cout << "[Engine] Failed to compile " << stageName << " shader: \n" << infoLog << std::endl;
            return false;
        }

        return true;
    }
}

LogenCore::Graphics::Shader::Shader(const char *fsPath) {
    this->Id = 0;
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // open files
        shaderFile.open(fsPath);
        std::stringstream fileStream;

        // read file's buffer contents into streams
        fileStream << shaderFile.rdbuf();

        // close file handlers
        shaderFile.close();

        const std::unordered_map<std::string, std::string> shaderStages = ParseShaderStages(fileStream.str());

        const auto vertexStageIt = shaderStages.find("vertex");
        if (vertexStageIt != shaderStages.end()) {
            vertexShaderCode = vertexStageIt->second;
        }

        const auto fragmentStageIt = shaderStages.find("fragment");
        if (fragmentStageIt != shaderStages.end()) {
            fragmentShaderCode = fragmentStageIt->second;
        }
    } catch (const std::ifstream::failure &) {
        std::cout << "[Engine] Failed to read shader at '" << fsPath << "'!" << std::endl;
    }
}

void LogenCore::Graphics::Shader::Compile() {
    if (vertexShaderCode.empty() || fragmentShaderCode.empty()) {
        std::cout << "[Engine] Shader source is missing #type vertex or #type fragment blocks." << std::endl;
        return;
    }

    const char *vertexCode = vertexShaderCode.c_str();
    const char *fragmentCode = fragmentShaderCode.c_str();

    const unsigned int vertexId = glCreateShader(GL_VERTEX_SHADER);
    if (!CompileStage(vertexId, vertexCode, "vertex")) {
        glDeleteShader(vertexId);
        return;
    }

    const unsigned int fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    if (!CompileStage(fragmentId, fragmentCode, "fragment")) {
        glDeleteShader(vertexId);
        glDeleteShader(fragmentId);
        return;
    }

    // Shader program
    this->Id = glCreateProgram();
    glAttachShader(this->Id, vertexId);
    glAttachShader(this->Id, fragmentId);
    glLinkProgram(this->Id);

    // print linking errors if any
    int success = 0;
    char infoLog[1024] = {0};
    glGetProgramiv(this->Id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->Id, 1024, nullptr, infoLog);
        std::cout << "[Engine] Failed to link shader program: \n" << infoLog << std::endl;
    }

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
}

void LogenCore::Graphics::Shader::Use() {
    glUseProgram(this->Id);
}

void LogenCore::Graphics::Shader::SetBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(this->Id, name.c_str()), (int) value);
}

void LogenCore::Graphics::Shader::SetInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(this->Id, name.c_str()), value);
}

void LogenCore::Graphics::Shader::SetFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(this->Id, name.c_str()), value);
}

void LogenCore::Graphics::Shader::SetMat4(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(this->Id, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void LogenCore::Graphics::Shader::SetVec3(const std::string &name, float x, float y, float z) {
    glUniform3f(glGetUniformLocation(this->Id, name.c_str()), x, y, z);
}

void LogenCore::Graphics::Shader::SetVec3(const std::string &name, glm::vec3 xyz) {
    glUniform3f(glGetUniformLocation(this->Id, name.c_str()), xyz.x, xyz.y, xyz.z);
}
