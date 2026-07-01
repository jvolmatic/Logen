#ifndef LOGEN_INPUT_H
#define LOGEN_INPUT_H
#include <memory>
#include <utility>
#include <vector>
#include <glad/gl.h>

#include "engine/Vector2.h"
#include "engine/CoreAPI.h"
#include "GLFW/glfw3.h"

namespace LogenCore::IO {
    class Input {
    public:
        Input(std::shared_ptr<GLFWwindow> window);
        ~Input() = default;

    public:
        void Update();

    public:
        LOGEN_API bool IsKeyPressed(int key);
        LOGEN_API bool IsMouseButtonPressed(int button);
        LOGEN_API std::pair<float, float> GetMousePosition();
        LOGEN_API bool IsKeyJustPressed(int key);
        LOGEN_API bool IsKeyJustReleased(int key);
        LOGEN_API void SetMouseCaptured(bool captured);

    public:
        Vector2 MouseDelta = {0, 0};
        bool bIsFirstMouseMovement = true;
        float LastMouseX = 0, LastMouseY = 0;
        float ScrollDelta = 0.f;
        bool scrolledLastFrame = false;

    protected:
        static void OnMouseCallback(GLFWwindow *window, double xpos, double ypos);
        static void OnScrollCallback(GLFWwindow *window, double xoffset, double yoffset);

    private:
        std::shared_ptr<GLFWwindow> glWindow;
        std::vector<int> keysPressedLastUpdate;
    };
}


#endif //LOGEN_INPUT_H
