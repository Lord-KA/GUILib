#pragma once

#include "color.hpp"

namespace g {
    class material {
    public:
        g::color color;
        float intence;

        float diffuse;
        float transp;
        float restit;

        bool isLumen;

        float absorb = 0;

        template<typename T>
        float reflect(const T &other, float cosA = 1, float cosB = 1) const
        {
            float res = (restit * cosB - cosA * other.restit) / (restit * cosB + cosA * other.restit);
            return res * res;
        }
    };
}
