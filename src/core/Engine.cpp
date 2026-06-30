#include "Engine.h"
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace LogenCore {
    Engine& Engine::GetInstance() {
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

        initialized = true;
        return true;
    }

    void Engine::Update() {
        if (!initialized || renderer == nullptr) {
            return;
        }

        this->renderer->RenderFrame();
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
}


