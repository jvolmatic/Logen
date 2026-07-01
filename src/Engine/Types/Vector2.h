#ifndef LOGEN_VECTOR2_H
#define LOGEN_VECTOR2_H
#include "../CoreAPI.h"
#include <glm/glm.hpp>

namespace LogenCore {
    class Vector2 {
    public:
        float x, y;

    public:
        Vector2() : x(0.0f), y(0.0f) {}
        Vector2(float x, float y) : x(x), y(y) {}
        Vector2(const glm::vec2& glmVec) : x(glmVec.x), y(glmVec.y) {}

    public:
        operator glm::vec2() const {
            return glm::vec2(x, y);
        }

        glm::vec2 toGLM() const {
            return glm::vec2(x, y);
        }

        static Vector2 fromGLM(const glm::vec2& glmVec) {
            return Vector2(glmVec);
        }
    };
}


#endif //LOGEN_VECTOR2_H
