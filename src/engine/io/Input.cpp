#include "Input.h"
#include "Engine.h"

LogenCore::IO::Input *LogenCore::IO::Input::Instance = nullptr;

LogenCore::IO::Input::Input(std::shared_ptr<GLFWwindow> &window) {
    Instance = this;
    this->window = window;

    int screenWidth, screenHeight;
    glfwGetWindowSize(this->window.get(), &screenWidth, &screenHeight);
    this->lastX = screenWidth / 2.0f;
    this->lastY = screenHeight / 2.0f;

    glfwSetCursorPosCallback(this->window.get(), this->OnMouseCallback);
    glfwSetScrollCallback(this->window.get(), this->OnScrollCallback);
}

void LogenCore::IO::Input::ProcessInput(float deltaTime) {
    if (glfwGetKey(window.get(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window.get(), true);

    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window.get(), GLFW_KEY_W) == GLFW_PRESS)
        Engine::GetInstance().GetActiveCamera()->SetPosition(
            Engine::GetInstance().GetActiveCamera()->GetPosition() + cameraSpeed * Engine::GetInstance().GetActiveCamera()->GetFront());
    if (glfwGetKey(window.get(), GLFW_KEY_S) == GLFW_PRESS)
        Engine::GetInstance().GetActiveCamera()->SetPosition(
            Engine::GetInstance().GetActiveCamera()->GetPosition() - cameraSpeed * Engine::GetInstance().GetActiveCamera()->GetFront());
    if (glfwGetKey(window.get(), GLFW_KEY_A) == GLFW_PRESS)
        Engine::GetInstance().GetActiveCamera()->SetPosition(
            Engine::GetInstance().GetActiveCamera()->GetPosition() - glm::normalize(
                glm::cross(Engine::GetInstance().GetActiveCamera()->GetFront(), Engine::GetInstance().GetActiveCamera()->GetUp())) *
            cameraSpeed);
    if (glfwGetKey(window.get(), GLFW_KEY_D) == GLFW_PRESS)
        Engine::GetInstance().GetActiveCamera()->SetPosition(
            Engine::GetInstance().GetActiveCamera()->GetPosition() + glm::normalize(
                glm::cross(Engine::GetInstance().GetActiveCamera()->GetFront(), Engine::GetInstance().GetActiveCamera()->GetUp())) *
            cameraSpeed);
}

void LogenCore::IO::Input::OnMouseCallback(GLFWwindow *window, double xposIn, double yposIn) {
    if (Instance == nullptr)
        return;

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (Instance->isFirstMouseMovement) {
        Instance->lastX = xpos;
        Instance->lastY = ypos;
        Instance->isFirstMouseMovement = false;
    }

    float xoffset = xpos - Instance->lastX;
    float yoffset = Instance->lastY - ypos; // reversed since y-coordinates range from bottom to top
    Instance->lastX = xpos;
    Instance->lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    Engine::GetInstance().GetActiveCamera()->SetYaw(Engine::GetInstance().GetActiveCamera()->GetYaw() + xoffset);
    Engine::GetInstance().GetActiveCamera()->SetPitch(Engine::GetInstance().GetActiveCamera()->GetPitch() + yoffset);

    if (Engine::GetInstance().GetActiveCamera()->GetPitch() > 89.0f)
        Engine::GetInstance().GetActiveCamera()->SetPitch(89.0f);
    if (Engine::GetInstance().GetActiveCamera()->GetPitch() < -89.0f)
        Engine::GetInstance().GetActiveCamera()->SetPitch(-89.0f);

    Engine::GetInstance().GetActiveCamera()->UpdateCamera();
}

void LogenCore::IO::Input::OnScrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    Engine::GetInstance().GetActiveCamera()->SetFOV(ceil(Engine::GetInstance().GetActiveCamera()->GetFOV() - yoffset));
    if (Engine::GetInstance().GetActiveCamera()->GetFOV() < 1)
        Engine::GetInstance().GetActiveCamera()->SetFOV(1);
    if (Engine::GetInstance().GetActiveCamera()->GetFOV() > 45)
        Engine::GetInstance().GetActiveCamera()->SetFOV(45);
}
