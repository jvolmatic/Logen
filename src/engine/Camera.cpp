#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

void LogenCore::Camera::UpdateCamera() {
    glm::vec3 direction;
    direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    direction.y = sin(glm::radians(this->pitch));
    direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->front = glm::normalize(direction);

    // also re-calculate the Right and Up vector
    // this->right = glm::normalize(glm::cross(this->front, this->up));
    // // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    // this->up = glm::normalize(glm::cross(this->right, this->front));
}

glm::mat4 LogenCore::Camera::GetViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

void LogenCore::Camera::SetFOV(unsigned int fov) {
    this->fov = fov;
    this->UpdateCamera();
}
