#ifndef LOGEN_SCENEOBJECT_H
#define LOGEN_SCENEOBJECT_H

#include <memory>
#include <string>

#include "Vector3.h"
#include "graphics/Shader.h"

namespace LogenCore {
    enum class SceneObjectType {
        Unknown,
        Camera,
        Light,
        ResourceMesh
    };

    class SceneObject {
    public:
        explicit SceneObject(
            Vector3 worldPos = {},
            Vector3 worldRot = {},
            SceneObjectType objectType = SceneObjectType::Unknown,
            std::string resourcePath = {}
        ) : worldPosition(worldPos), worldRotation(worldRot), objectType(objectType), resourcePath(std::move(resourcePath)) {
        }

        virtual ~SceneObject() = default;

    public:
        Vector3 worldPosition;
        Vector3 worldRotation;
        SceneObjectType objectType = SceneObjectType::Unknown;
        std::string resourcePath;
    };
}


#endif //LOGEN_SCENEOBJECT_H
