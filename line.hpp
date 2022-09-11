#pragma once

#include <iostream>
#include <cmath>

#include "vector.hpp"
#include "plain.hpp"
#include "color.hpp"

namespace g {

    class line {
    private:
        class kernel {
        public:
            size_t x1;
            size_t y1;
            size_t x2;
            size_t y2;
            size_t w;

        } ker;

    public:
        line(const line &other) : ker(other.ker) {}

        line(size_t x1, size_t y1, const vector v)
        {
            ker.x1 = x1;
            ker.y1 = y1;
            ker.x2 = v.getKer().x;
            ker.x2 = v.getKer().y;
        }

        line(size_t x1, size_t y1, size_t x2, size_t y2)
        {
            ker.x1 = x1;
            ker.y1 = y1;
            ker.x2 = x2;
            ker.y2 = y2;
        }

        ~line()
        {
            ker.x1 = NAN;
            ker.y1 = NAN;
            ker.x2 = NAN;
            ker.y2 = NAN;
        }

        bool operator==(const line &other)
        {
            return (ker.x1 == other.ker.x1 && ker.y1 == other.ker.y1 && ker.x2 == other.ker.x2 && ker.y2 == other.ker.y2);
        }

        void draw2plane(plain &p, color c)
        {
            size_t maxX = std::max(ker.x1, ker.x2);
            size_t maxY = std::max(ker.y1, ker.y2);
            size_t minX = std::min(ker.x1, ker.x2);
            size_t minY = std::min(ker.y1, ker.y2);
            assert(maxX < p.getHeight() && maxY < p.getWidth());
            for (size_t x = minX; x != maxX; ++x) {
                for (size_t y = minY; y != maxY; ++y) {
                    if (((x - ker.x1) * (ker.y2 - ker.y1) - (y - ker.y1) * (ker.x2 - ker.x1)) < ker.w)
                        p(x, y) = c;
                }
            }
        }
    };
}
