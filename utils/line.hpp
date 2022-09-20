#pragma once

#include <iostream>
#include <cmath>

#include "vector2f.hpp"
#include "color.hpp"

namespace g {

    class line {
    private:
        class kernel {
        public:
            int x1;
            int y1;
            int x2;
            int y2;
            int w;

        } ker;

    public:
        line(const line &other) : ker(other.ker) {}

        line(int x1, int y1, const vector2f v, int w = 1)
        {
            ker.x1 = x1;
            ker.y1 = y1;
            ker.x2 = x1 + v.getKer().x;
            ker.y2 = y1 + v.getKer().y;
            ker.w = w;
        }

        line(int x1, int y1, int x2, int y2, int w = 1)
        {
            ker.x1 = x1;
            ker.y1 = y1;
            ker.x2 = x2;
            ker.y2 = y2;
            ker.w = w;
        }

        ~line()
        {
            ker.x1 = -1;
            ker.y1 = -1;
            ker.x2 = -1;
            ker.y2 = -1;
        }

        kernel getKer() const
        {
            return ker;
        }

        bool operator==(const line &other)
        {
            return (ker.x1 == other.ker.x1 && ker.y1 == other.ker.y1 && ker.x2 == other.ker.x2 && ker.y2 == other.ker.y2);
        }
    };
}
