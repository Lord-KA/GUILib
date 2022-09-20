#pragma once

#include "object3d.hpp"

namespace g {
    class sphere {
    private:
        float rad;

    public:
        sphere(vector3f c, float r) : center(c), rad(r) {}


    };
}
