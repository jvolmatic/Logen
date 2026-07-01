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

        renderer = std::make_shared<LogenCore::Graphics::Renderer>();
        if (!renderer->Initialize(title, width, height)) {
            std::cerr << "[Engine] Failed to initialize the renderer." << std::endl;
            return false;
        }

        input = std::make_shared<LogenCore::IO::Input>(this->renderer->GetWindow());

        initialized = true;
        return true;
    }

    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame
    void Engine::Update() {
        if (!initialized || renderer == nullptr) {
            return;
        }

        this->input->ProcessInput(deltaTime);
        this->renderer->RenderFrame();

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }

    void Engine::Shutdown() {
        if (!initialized) {
            return;
        }

        renderer = nullptr;
        initialized = false;
    }

    bool Engine::IsRunning() const {
        if (!initialized) {
            return false;
        }

        return this->renderer->IsAlive();
    }

    void Engine::SwapScene(Scene &otherScene) {
        this->scene = &otherScene;
        this->scene->isRoot = true;
    }

    Scene *Engine::GetTree() {
        return this->scene;
    }
}
