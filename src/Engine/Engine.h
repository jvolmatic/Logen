#ifndef LOGEN_ENGINE_H
#define LOGEN_ENGINE_H

#include <memory>
#include "Engine/CoreAPI.h"
#include "Graphics/Renderer.h"
#include "Scene.h"
#include "Types/Vector2.h"
#include "IO/Input.h"

namespace LogenCore {
    class Engine {
    public:
        // Delete copy/move constructors and assignment operators
        Engine(const Engine &) = delete;
        Engine &operator=(const Engine &) = delete;
        Engine(Engine &&) = delete;
        Engine &operator=(Engine &&) = delete;

    public:
        static LOGEN_API Engine &GetInstance();
        LOGEN_API bool Initialize(int width, int height, const char *title);
        LOGEN_API void Update();
        LOGEN_API void Shutdown();
        LOGEN_API [[nodiscard]] bool IsRunning() const;
        LOGEN_API void SwapScene(Scene &scene);
        LOGEN_API Scene *GetTree();
        LOGEN_API Vector2 GetWindowSize();
        std::shared_ptr<Graphics::Renderer> Renderer = nullptr;
        std::shared_ptr<IO::Input> Input = nullptr;

    public:
        std::shared_ptr<Camera> &GetActiveCamera() { return this->Renderer->GetActiveCamera(); }

    private:
        Engine() = default;
        ~Engine() = default;

    public:
        float deltaTime = 0.0f; // Time between current frame and last frame

    private:
        float lastFrame = 0.0f; // Time of last frame

    private:
        bool initialized = false;
        LogenCore::Scene *scene = nullptr;
    };
}


#endif // LOGEN_ENGINE_H
