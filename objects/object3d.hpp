#pragma once

#include "vector3f.hpp"
#include "material.hpp"

static const float EPS = 0.02;

namespace g {
    class object3d {
    public:
        g::vector3f center;
        g::material material;

        object3d(g::vector3f c, g::material m) : center(c), material(m) {}

        virtual void setPosition(g::vector3f pos) = delete;
        virtual void move(g::vector3f delta) = delete;

        virtual void outline() = delete;

        virtual float traverse(const object3d &other) = delete;
    };
}
