#ifndef LOGEN_ENGINE_H
#define LOGEN_ENGINE_H

#include <memory>
#include "core/CoreAPI.h"
#include "graphics/Renderer.h"
#include <GLFW/glfw3.h>

#include "Scene.h"

namespace LogenCore {
    class Engine {
    public:
        // Delete copy/move constructors and assignment operators
        Engine(const Engine &) = delete;
        Engine &operator=(const Engine &) = delete;
        Engine(Engine &&) = delete;
        Engine &operator=(Engine &&) = delete;

        static LOGEN_API Engine &GetInstance();

        LOGEN_API bool Initialize(int width, int height, const char *title);
        LOGEN_API void Update();
        LOGEN_API void Shutdown();
        LOGEN_API [[nodiscard]] bool IsRunning() const;
        LOGEN_API void SwapScene(Scene &scene);
        LOGEN_API Scene *GetTree();

    private:
        Engine() = default;
        ~Engine() = default;

    private:
        std::shared_ptr<LogenCore::Graphics::Renderer> renderer = nullptr;
        bool initialized = false;
        LogenCore::Scene *scene = nullptr;
    };
}


#endif // LOGEN_ENGINE_H
