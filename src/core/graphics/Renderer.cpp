#include "Renderer.h"
#include <iostream>
#include "core/Camera.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>

LogenCore::Graphics::Renderer::~Renderer() {
    if (this->window != nullptr) {
        glfwDestroyWindow(this->window.get());
    }

    glfwTerminate();
}

bool LogenCore::Graphics::Renderer::Initialize(const char *windowTitle, int width, int height) {
    this->screenWidth = width;
    this->screenHeight = height;

    // Create a default camera
    this->activeCamera = std::make_shared<LogenCore::Camera>();

    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->window = std::shared_ptr<GLFWwindow>(
        glfwCreateWindow(width, height, windowTitle, nullptr, nullptr),
        glfwDestroyWindow
    );

    if (this->window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;

        glfwDestroyWindow(this->window.get());
        glfwTerminate();

        return false;
    }

    glfwMakeContextCurrent(this->window.get());
    if (gladLoadGL(reinterpret_cast<GLADloadfunc>(glfwGetProcAddress)) == 0) {
        std::cout << "Failed to initialize GLAD" << std::endl;

        glfwDestroyWindow(this->window.get());
        glfwTerminate();

        return false;
    }

    // OpenGL flags
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, this->screenWidth, this->screenHeight);

    // OpenGL callbacks
    glfwSetFramebufferSizeCallback(this->window.get(), [](GLFWwindow *window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    return true;
}

bool LogenCore::Graphics::Renderer::IsAlive() const {
    return !glfwWindowShouldClose(this->window.get());
}

void LogenCore::Graphics::Renderer::RenderFrame() {
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glfwSwapBuffers(this->window.get());
    glfwPollEvents();
}
