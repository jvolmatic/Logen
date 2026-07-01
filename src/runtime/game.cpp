#include <iostream>

#include "core/Engine.h"
#include "core/Scene.h"

int main() {
    LogenCore::Engine &engine = LogenCore::Engine::GetInstance();
    if (!engine.Initialize(1280, 720, "Game")) {
        std::cerr << "[RUNTIME] Engine initialization failed." << std::endl;
        return 1;
    }

    // Load scene
    LogenCore::Scene root("scenes/test.scene", "/");
    if (!root.Instantiate()) {
        std::cerr << "[RUNTIME] Failed to instantiate the root scene." << std::endl;
        return 1;
    }

    // Set scene as the root scene
    engine.SwapScene(root);

    // Main loop
    while (engine.IsRunning()) {
        engine.Update();
    }

    engine.Shutdown();
    return 0;
}
