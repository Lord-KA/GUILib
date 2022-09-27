#pragma once

#include "object3d.hpp"

namespace g {
    class sphere : public object3d {
    public:
        float rad;

        sphere(vector3f c, float r, g::material m) : object3d(c, m), rad(r) {}

    };
}
