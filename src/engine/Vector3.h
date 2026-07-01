#ifndef LOGEN_VECTOR3_H
#define LOGEN_VECTOR3_H
#include "CoreAPI.h"
#include <glm/glm.hpp>

namespace LogenCore {
    class Vector3 {
    public:
        float x, y, z;

    public:
        Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
        Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
        Vector3(const glm::vec3& glmVec) : x(glmVec.x), y(glmVec.y), z(glmVec.z) {}

    public:
        operator glm::vec3() const {
            return glm::vec3(x, y, z);
        }

        glm::vec3 toGLM() const {
            return glm::vec3(x, y, z);
        }

        static Vector3 fromGLM(const glm::vec3& glmVec) {
            return Vector3(glmVec);
        }
    };
}


#endif //LOGEN_VECTOR3_H
