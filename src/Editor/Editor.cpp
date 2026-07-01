#include <iostream>

#include "EditorInput.h"
#include "Engine/Engine.h"
#include "Engine/Scene.h"

int main() {
    LogenCore::Engine &engine = LogenCore::Engine::GetInstance();
    if (!engine.Initialize(1280, 720, "Game")) {
        std::cerr << "[EDITOR] Engine initialization failed." << std::endl;
        return 1;
    }

    // Load scene
    LogenCore::Scene root("scenes/test.scene", "/");
    if (!root.Instantiate()) {
        std::cerr << "[EDITOR] Failed to instantiate the root scene." << std::endl;
        return 1;
    }

    // Set scene as the root scene
    engine.SwapScene(root);

    EditorInput input;

    // Main loop
    float deltaTime = 0.0f; // Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame
    while (engine.IsRunning()) {
        input.ProcessInput(deltaTime);
        engine.Update();

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }

    engine.Shutdown();
    return 0;
}
