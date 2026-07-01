#ifndef LOGEN_SHADER_H
#define LOGEN_SHADER_H
#include <string>

#include "glm/fwd.hpp"

namespace LogenCore::Graphics {
    class Shader {
    public:
        unsigned int Id;
        Shader(const char *fsPath);

        void Compile();
        void Use();
        void SetBool(const std::string &name, bool value) const;
        void SetInt(const std::string &name, int value) const;
        void SetFloat(const std::string &name, float value) const;
        void SetMat4(const std::string &name, const glm::mat4 &mat) const;
        void SetVec3(const std::string &name, float x, float y, float z);
        void SetVec3(const std::string &name, glm::vec3 xyz);

    private:
        std::string vertexShaderCode;
        std::string fragmentShaderCode;
    };
}


#endif //LOGEN_SHADER_H
