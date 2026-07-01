#ifndef LOGEN_DIRECTIONALLIGHT_H
#define LOGEN_DIRECTIONALLIGHT_H
#include "Light.h"

namespace LogenCore {
    class DirectionalLight : public Light {
    public:
        explicit DirectionalLight(Vector3 worldPos = {}, Vector3 worldRot = {}, Vector3 direction = {}) :
            Light(worldPos, worldRot),
            direction(direction) {
            this->type = LightType::DIRECTIONAL;
        }

        Vector3 direction;
    };
}


#endif //LOGEN_DIRECTIONALLIGHT_H
