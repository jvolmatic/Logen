#include "Input.h"

#include <iostream>

#include "Engine.h"

LogenCore::IO::Input::Input(std::shared_ptr<GLFWwindow> window) {
    this->glWindow = std::move(window);
    glfwSetCursorPosCallback(this->glWindow.get(), this->OnMouseCallback);
    glfwSetScrollCallback(this->glWindow.get(), this->OnScrollCallback);
}

void LogenCore::IO::Input::OnMouseCallback(GLFWwindow *window, double xposIn, double yposIn) {
    auto &input = Engine::GetInstance().Input;
    if (input == nullptr)
        return;

    auto xpos = static_cast<float>(xposIn);
    auto ypos = static_cast<float>(yposIn);

    if (input->bIsFirstMouseMovement) {
        input->LastMouseX = xpos;
        input->LastMouseY = ypos;
        input->bIsFirstMouseMovement = false;
        input->MouseDelta = {0.0f, 0.0f};
        return;
    }

    auto xoffset = xpos - input->LastMouseX;
    auto yoffset = input->LastMouseY - ypos; // reversed since y-coordinates range from bottom to top

    input->LastMouseX = xpos;
    input->LastMouseY = ypos;
    input->MouseDelta = {xoffset, yoffset};
}

void LogenCore::IO::Input::OnScrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    auto &input = Engine::GetInstance().Input;
    if (input == nullptr)
        return;

    input->ScrollDelta = static_cast<float>(yoffset);
    input->scrolledLastFrame = true;
}

void LogenCore::IO::Input::Update() {
    MouseDelta = {0.0f, 0.0f};
    keysPressedLastUpdate.clear();
    for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key) {
        if (glfwGetKey(glWindow.get(), key) == GLFW_PRESS) {
            keysPressedLastUpdate.push_back(key);
        }
    }

    if (scrolledLastFrame) {
        ScrollDelta = 0.0f;
    }
    scrolledLastFrame = false;
}

bool LogenCore::IO::Input::IsKeyPressed(int key) {
    return glfwGetKey(glWindow.get(), key) == GLFW_PRESS;
}

bool LogenCore::IO::Input::IsMouseButtonPressed(int button) {
    return glfwGetMouseButton(glWindow.get(), button) == GLFW_PRESS;
}

std::pair<float, float> LogenCore::IO::Input::GetMousePosition() {
    double xpos, ypos;
    glfwGetCursorPos(glWindow.get(), &xpos, &ypos);
    return {static_cast<float>(xpos), static_cast<float>(ypos)};
}

bool LogenCore::IO::Input::IsKeyJustPressed(int key) {
    return std::find(keysPressedLastUpdate.begin(), keysPressedLastUpdate.end(), key) != keysPressedLastUpdate.end();
}

bool LogenCore::IO::Input::IsKeyJustReleased(int key) {
    return std::find(keysPressedLastUpdate.begin(), keysPressedLastUpdate.end(), key) == keysPressedLastUpdate.end();
}

void LogenCore::IO::Input::SetMouseCaptured(bool captured) {
    glfwSetInputMode(glWindow.get(), GLFW_CURSOR, captured ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}
