#ifndef LOGEN_RENDERER_H
#define LOGEN_RENDERER_H
#include <memory>
#include "core/CoreAPI.h"
#include "core/Camera.h"
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

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

    private:
        int screenWidth = 0, screenHeight = 0;
        std::shared_ptr<GLFWwindow> window;
        std::shared_ptr<LogenCore::Camera> activeCamera;
    };
}

#endif //LOGEN_RENDERER_H
