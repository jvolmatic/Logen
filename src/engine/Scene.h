#ifndef LOGEN_SCENE_H
#define LOGEN_SCENE_H

#include <memory>
#include <string>
#include <vector>

#include "SceneObject.h"

namespace LogenCore {
    class Scene {
    public:
        Scene( const char *fsPath, const char *treePath) {
            this->fsPath = std::string(fsPath);
            this->treePath = std::string(treePath);
        }

        ~Scene() = default;

    public:
        LOGEN_API bool Instantiate();

    public:
        std::vector<std::unique_ptr<SceneObject>> objects;
        std::vector<std::unique_ptr<Graphics::Shader>> shaders;

    public:
        std::string name;
        std::string fsPath;
        std::string treePath;
        bool isRoot = false;
    };
}


#endif //LOGEN_SCENE_H
