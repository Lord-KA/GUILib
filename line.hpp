#pragma once

#include <iostream>
#include <cmath>

#include "vector.hpp"
#include "plain.hpp"
#include "color.hpp"

#include "stdio.h" // FIXME

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

        line(size_t x1, size_t y1, const vector v, size_t w = 1)
        {
            ker.x1 = x1;
            ker.y1 = y1;
            ker.x2 = v.getKer().x;
            ker.x2 = v.getKer().y;
            ker.w = w;
        }

        line(size_t x1, size_t y1, size_t x2, size_t y2, size_t w = 1)
        {
            ker.x1 = x1;
            ker.y1 = y1;
            ker.x2 = x2;
            ker.y2 = y2;
            ker.w = w;
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
            long maxX = std::max(ker.x1, ker.x2);
            long minX = std::min(ker.x1, ker.x2);
            long maxY = std::max(ker.y1, ker.y2);
            long minY = std::min(ker.y1, ker.y2);
            long deltaX = maxX - minX;
            long deltaY = maxY - minY;
            double error = 0;
            double deltaErr = (deltaY + 1) / (deltaX + 1);
            long y = minY;
            assert(maxX < p.getHeight() && maxY < p.getWidth());
            for (long x = minX; x <= maxX; ++x) {
                p(x, y) = c;
                error += deltaErr;
                if (error >= 1.0) {
                    ++y;
                    error -= 1.0;
                }
            }
        }
    };
}
