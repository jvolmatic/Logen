#ifndef LOGEN_CAMERA_H
#define LOGEN_CAMERA_H
#include "CoreAPI.h"
#include "glm/fwd.hpp"
#include "glm/vec3.hpp"

namespace LogenCore {
    class Camera {
    public:
        LOGEN_API void UpdateCamera();

        void SetPosition(glm::vec3 pos) { this->position = pos; }
        glm::vec3 GetPosition() { return this->position; };
        glm::vec3 GetFront() { return this->front; };
        glm::vec3 GetUp() { return this->up; };
        void SetYaw(float yaw) { this->yaw = yaw; }
        void SetPitch(float pitch) { this->pitch = pitch; }
        float GetYaw() { return this->yaw; }
        float GetPitch() { return this->pitch; }

        glm::mat4 GetViewMatrix();

        void SetFOV(unsigned int fov);

        unsigned int GetFOV() { return this->fov; }

    private:
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
        float yaw = -90.0f, pitch = 0.0f;
        unsigned int fov = 45;
    };
}



#endif //LOGEN_CAMERA_H