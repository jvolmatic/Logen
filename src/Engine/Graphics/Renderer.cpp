#include "Renderer.h"
#include <iostream>
#include "Engine/Camera.h"

#include "Engine.h"
#include "Light.h"
#include "DirectionalLight.h"
#include "MeshResource.h"
#include "PointLight.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

LogenCore::Graphics::Renderer::~Renderer() {
    if (this->window != nullptr) {
        glfwDestroyWindow(this->window.get());
    }

    glfwTerminate();
}

bool LogenCore::Graphics::Renderer::Initialize(const char *windowTitle, int width, int height) {
    this->screenWidth = width;
    this->screenHeight = height;

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
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // No camera? Find the first one in scene and set it active
    if (this->activeCamera == nullptr) {
        auto camera = std::make_shared<LogenCore::Camera>();
        for (std::unique_ptr<SceneObject> &scene_object: Engine::GetInstance().GetTree()->objects) {
            if (scene_object->objectType == SceneObjectType::Camera) {
                camera->SetPosition(scene_object->worldPosition);
                break;
            }
        }
        this->activeCamera = camera;
    }

    // Calc projection & view matrices
    projection = glm::perspective(glm::radians((float) this->activeCamera->GetFOV()),
                                  (float) this->screenWidth / (float) this->screenHeight, 0.1f, 100.0f);
    view = this->activeCamera->GetViewMatrix();

    // Use shaders in the scene
    // TODO in the future, scenes will have children scenes, loop through these..
    for (std::unique_ptr<Graphics::Shader> &shader: Engine::GetInstance().GetTree()->shaders) {
        shader->Use();

        // Set shader uniforms
        shader->SetMat4("projection", projection);
        shader->SetMat4("view", view);
        shader->SetVec3("viewPos", this->activeCamera->GetPosition());

        int pointLightCount = 0;
        for (std::unique_ptr<SceneObject> &scene_object: Engine::GetInstance().GetTree()->objects) {
            // Handle lights
            if (scene_object->objectType == SceneObjectType::Light) {
                Light *light = static_cast<Light *>(scene_object.get());
                if (light == nullptr)
                    continue;

                switch (light->type) {
                    case LightType::DIRECTIONAL: {
                        auto *dirLight = dynamic_cast<DirectionalLight *>(light);
                        if (dirLight != nullptr) {
                            shader->SetVec3("dirLight.direction", dirLight->direction.x, dirLight->direction.y, dirLight->direction.z);
                            shader->SetVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
                            shader->SetVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
                            shader->SetVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
                        }
                        break;
                    }
                    case LightType::SPOT:
                        //TODO
                        break;
                    case LightType::POINT: {
                        auto *pointLight = dynamic_cast<PointLight *>(light);
                        if (pointLight != nullptr) {
                            std::string baseKey = "pointLights[" + std::to_string(pointLightCount) + "]";
                            shader->SetVec3(baseKey + ".position", pointLight->worldPosition.toGLM());
                            shader->SetVec3(baseKey + ".ambient", 0.05f, 0.05f, 0.05f);
                            shader->SetVec3(baseKey + ".diffuse", pointLight->RGB.toGLM());
                            shader->SetVec3(baseKey + ".specular", 1.0f, 1.0f, 1.0f);
                            shader->SetFloat(baseKey + ".intensity", pointLight->Intensity);
                            shader->SetFloat(baseKey + ".constant", 1.0f);
                            shader->SetFloat(baseKey + ".linear", 0.09f);
                            shader->SetFloat(baseKey + ".quadratic", 0.032f);
                            pointLightCount++;
                        }
                        break;
                    }
                }
            }

            // Handle models
            auto *meshRes = dynamic_cast<MeshResource *>(scene_object.get());
            if (meshRes == nullptr)
                continue;

            model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(meshRes->worldPosition));
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)); // it's a bit too big for our scene, so scale it down // TODO
            shader->SetMat4("model", model);
            meshRes->model->Draw(*shader);
        }

        // Tell shader how many point lights are active
        shader->SetInt("numPointLights", static_cast<int>(pointLightCount));
    }

    glfwSwapBuffers(this->window.get());
    glfwPollEvents();
}
