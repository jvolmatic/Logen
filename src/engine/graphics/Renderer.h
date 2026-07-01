#ifndef LOGEN_RENDERER_H
#define LOGEN_RENDERER_H
#include <memory>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "engine/CoreAPI.h"
#include "engine/Camera.h"
#include <glm/glm.hpp>
#include <utility>

namespace LogenCore::Graphics {
    enum ViewMode {
        FACES,
        POLYGONS
    };

    class Renderer {
    public:
        Renderer() = default;
        ~Renderer();

        bool LOGEN_API Initialize(const char *windowTitle, int width, int height);
        [[nodiscard]] bool LOGEN_API IsAlive() const;
        void LOGEN_API RenderFrame();
        [[nodiscard]] std::shared_ptr<GLFWwindow> &GetWindow() { return window; }
        [[nodiscard]] std::shared_ptr<LogenCore::Camera> &GetActiveCamera() { return activeCamera; }

    private:
        int screenWidth = 0, screenHeight = 0;
        std::shared_ptr<GLFWwindow> window;
        std::shared_ptr<LogenCore::Camera> activeCamera;
    };
}

#endif //LOGEN_RENDERER_H
