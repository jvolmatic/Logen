#include <iostream>

#include "core/Engine.h"

int main() {
    LogenCore::Engine& engine = LogenCore::Engine::GetInstance();
    if (!engine.Initialize(1280, 720, "Game")) {
        std::cerr << "[RUNTIME] Engine initialization failed." << std::endl;
        return 1;
    }

    // Main loop
    while (engine.IsRunning()) {
        engine.Update();
    }

    engine.Shutdown();
    return 0;
}