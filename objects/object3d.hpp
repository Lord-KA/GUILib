#pragma once

#include "vector3f.hpp"

static const float EPS = 0.02;

namespace g {
    class object3d {
    private:
        g::vector3f center;

    public:
        virtual void setPosition(g::vector3f pos);
        virtual void move(g::vector3f delta);

        virtual void outline();

        virtual bool traverse(const object3d &other);
    };
}
