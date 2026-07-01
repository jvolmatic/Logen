#include "Engine.h"
#include <iostream>

namespace LogenCore {
    Engine &Engine::GetInstance() {
        static Engine instance;
        return instance;
    }

    // Private implementation methods
    bool Engine::Initialize(int width, int height, const char *title) {
        if (initialized) {
            return true;
        }

        Renderer = std::make_shared<LogenCore::Graphics::Renderer>();
        if (!Renderer->Initialize(title, width, height)) {
            std::cerr << "[Engine] Failed to initialize the renderer." << std::endl;
            return false;
        }

        Input = std::make_shared<LogenCore::IO::Input>(this->Renderer->GetWindow());

        initialized = true;
        return true;
    }

    void Engine::Update() {
        if (!initialized || Renderer == nullptr) {
            return;
        }

        this->Input->Update();
        this->Renderer->RenderFrame();

        // Update delta time
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }

    void Engine::Shutdown() {
        if (!initialized) {
            return;
        }

        Renderer = nullptr;
        initialized = false;
    }

    bool Engine::IsRunning() const {
        if (!initialized) {
            return false;
        }

        return this->Renderer->IsAlive();
    }

    void Engine::SwapScene(Scene &otherScene) {
        this->scene = &otherScene;
        this->scene->isRoot = true;
    }

    Scene *Engine::GetTree() {
        return this->scene;
    }

    Vector2 Engine::GetWindowSize() {
        int width, height;
        if (this->Renderer == nullptr) {
            return {0, 0};
        }

        glfwGetWindowSize(this->Renderer->GetWindow().get(), &width, &height);
        return {static_cast<float>(width), static_cast<float>(height)};
    }
}
