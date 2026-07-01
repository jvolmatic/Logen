#ifndef LOGEN_MESHRESOURCE_H
#define LOGEN_MESHRESOURCE_H
#include "SceneObject.h"
#include "Graphics/Model.h"

namespace LogenCore {
    class MeshResource : public SceneObject {
    public:
        explicit MeshResource(Vector3 worldPos = {},
                              Vector3 worldRot = {},
                              const std::string &modelPath = "",
                              const std::string &shaderPath = ""
        ) : SceneObject(worldPos, worldRot, SceneObjectType::ResourceMesh, modelPath), modelPath(modelPath), shaderPath(shaderPath) {
            this->model = std::make_shared<Graphics::Model>(this->modelPath.c_str());
        }

        ~MeshResource() override = default;

    public:
        std::string modelPath;
        std::string shaderPath;
        std::shared_ptr<Graphics::Model> model = nullptr;
    };
}


#endif //LOGEN_MESHRESOURCE_H
