#pragma once

#include "object3d.hpp"

namespace g {
    class line : public object3d {
    private:
        vector3f dir;

    public:
        line(vector3f c, vector3f d) : center(c), dir(d) {}

        line(vector3d c, float a, float b, float c) : center(c)
        {
            dir = {a, b, c};
        }

        bool traverse(const line &other)
        {
            // TODO
        }
    };
}
