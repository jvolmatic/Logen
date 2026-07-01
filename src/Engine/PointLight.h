#ifndef LOGEN_POINTLIGHT_H
#define LOGEN_POINTLIGHT_H
#include "Light.h"


namespace LogenCore {
    class PointLight : public Light {
    public:
        explicit PointLight(Vector3 worldPos = {}, Vector3 worldRot = {}, Vector3 RGB = {}, float Intensity = 1.0f) :
            Light(worldPos, worldRot), RGB(RGB), Intensity(Intensity) {
            this->type = LightType::POINT;
        }

    public:
        Vector3 RGB = {};
        float Intensity = 1.0f;
    };
}


#endif //LOGEN_POINTLIGHT_H
