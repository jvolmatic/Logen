#ifndef LOGEN_LIGHT_H
#define LOGEN_LIGHT_H

#include <map>
#include <optional>
#include <string>

#include "SceneObject.h"
#include "Vector3.h"

namespace LogenCore {
    enum LightType {
        DIRECTIONAL = 0,
        POINT = 1,
        SPOT = 2
    };

    class Light : public SceneObject {
    public:
        explicit Light(Vector3 worldPos = {}, Vector3 worldRot = {}, LightType type = POINT, Vector3 dir = {})
            : SceneObject(worldPos, worldRot, SceneObjectType::Light), type(type), direction(dir) {
        }

        ~Light() override = default;

    public:
        inline static const std::map<std::string, LightType> LightTypes = {
            {"DIRECTIONAL_LIGHT", DIRECTIONAL},
            {"POINT_LIGHT", POINT},
            {"SPOT_LIGHT", SPOT}
        };

        static std::optional<LightType> FromSceneDirective(const std::string &directive) {
            const auto lightTypeIt = LightTypes.find(directive);
            if (lightTypeIt == LightTypes.end()) {
                return std::nullopt;
            }

            return lightTypeIt->second;
        }

    public:
        LightType type = POINT;
        Vector3 direction;
    };
}


#endif //LOGEN_LIGHT_H
