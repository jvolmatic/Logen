#include "EditorInput.h"

#include <algorithm>
#include <iostream>

#include "Engine/Engine.h"

void EditorInput::ProcessInput(float deltaTime) {
    if (LogenCore::Engine::GetInstance().GetActiveCamera() == nullptr)
        return;

    // Movement
    float cameraSpeed = movementSpeed * deltaTime;
    if (LogenCore::Engine::GetInstance().Input->IsKeyPressed(GLFW_KEY_W))
        LogenCore::Engine::GetInstance().GetActiveCamera()->SetPosition(
            LogenCore::Engine::GetInstance().GetActiveCamera()->GetPosition() + cameraSpeed * LogenCore::Engine::GetInstance().
            GetActiveCamera()->GetFront());
    if (LogenCore::Engine::GetInstance().Input->IsKeyPressed(GLFW_KEY_S))
        LogenCore::Engine::GetInstance().GetActiveCamera()->SetPosition(
            LogenCore::Engine::GetInstance().GetActiveCamera()->GetPosition() - cameraSpeed * LogenCore::Engine::GetInstance().
            GetActiveCamera()->GetFront());
    if (LogenCore::Engine::GetInstance().Input->IsKeyPressed(GLFW_KEY_A))
        LogenCore::Engine::GetInstance().GetActiveCamera()->SetPosition(
            LogenCore::Engine::GetInstance().GetActiveCamera()->GetPosition() - glm::normalize(
                glm::cross(LogenCore::Engine::GetInstance().GetActiveCamera()->GetFront(),
                           LogenCore::Engine::GetInstance().GetActiveCamera()->GetUp())) *
            cameraSpeed);
    if (LogenCore::Engine::GetInstance().Input->IsKeyPressed(GLFW_KEY_D))
        LogenCore::Engine::GetInstance().GetActiveCamera()->SetPosition(
            LogenCore::Engine::GetInstance().GetActiveCamera()->GetPosition() + glm::normalize(
                glm::cross(LogenCore::Engine::GetInstance().GetActiveCamera()->GetFront(),
                           LogenCore::Engine::GetInstance().GetActiveCamera()->GetUp())) *
            cameraSpeed);

    // Rotation
    if (LogenCore::Engine::GetInstance().Input->IsMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT)) {
        const float sensitivity = 5.f;
        float xoffset = LogenCore::Engine::GetInstance().Input->MouseDelta.x * sensitivity * deltaTime;
        float yoffset = LogenCore::Engine::GetInstance().Input->MouseDelta.y * sensitivity * deltaTime;

        LogenCore::Engine::GetInstance().GetActiveCamera()->SetYaw(LogenCore::Engine::GetInstance().GetActiveCamera()->GetYaw() + xoffset);
        LogenCore::Engine::GetInstance().GetActiveCamera()->SetPitch(
            LogenCore::Engine::GetInstance().GetActiveCamera()->GetPitch() + yoffset);

        if (LogenCore::Engine::GetInstance().GetActiveCamera()->GetPitch() > 89.0f)
            LogenCore::Engine::GetInstance().GetActiveCamera()->SetPitch(89.0f);
        if (LogenCore::Engine::GetInstance().GetActiveCamera()->GetPitch() < -89.0f)
            LogenCore::Engine::GetInstance().GetActiveCamera()->SetPitch(-89.0f);

        LogenCore::Engine::GetInstance().GetActiveCamera()->UpdateCamera();
        LogenCore::Engine::GetInstance().Input->SetMouseCaptured(true);

        // Speed change
        if (LogenCore::Engine::GetInstance().Input->ScrollDelta != 0) {
            movementSpeed -= LogenCore::Engine::GetInstance().Input->ScrollDelta * 0.1f;
            movementSpeed = std::clamp(movementSpeed, 0.0f, 100.0f);
        }
    } else {
        LogenCore::Engine::GetInstance().Input->SetMouseCaptured(false);
    }

    // Sprint
    const bool sprintPressed = LogenCore::Engine::GetInstance().Input->IsKeyPressed(GLFW_KEY_LEFT_SHIFT);
    if (sprintPressed && !bWasSprintKeyPressedLastFrame) {
        movementSpeed = std::clamp(movementSpeed * sprintSpeedMultiplier, 0.0f, 100.0f);
    } else if (!sprintPressed && bWasSprintKeyPressedLastFrame) {
        movementSpeed = std::clamp(movementSpeed / sprintSpeedMultiplier, 0.0f, 100.0f);
    }
    bWasSprintKeyPressedLastFrame = sprintPressed;
}
