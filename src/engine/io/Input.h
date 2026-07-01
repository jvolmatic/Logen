#ifndef LOGEN_INPUT_H
#define LOGEN_INPUT_H
#include <memory>
#include <glad/gl.h>
#include "GLFW/glfw3.h"

namespace LogenCore::IO {
    class Input {
    public:
        static Input* Instance; // TODO singleton interface
        Input(std::shared_ptr<GLFWwindow> &window);
        ~Input() = default;

        void ProcessInput(float deltaTime);

    protected:
        static void OnMouseCallback(GLFWwindow *window, double xpos, double ypos);
        static void OnScrollCallback(GLFWwindow *window, double xoffset, double yoffset);

    private:
        float lastX, lastY;
        std::shared_ptr<GLFWwindow> window;
        bool isFirstMouseMovement = true;
    };
}


#endif //LOGEN_INPUT_H