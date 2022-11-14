#pragma once

#include <iostream>
#include <cmath>

namespace g {

    class vector2f {
    public:
        class kernel {
        public:
            float x;
            float y;

        } ker;

        vector2f(float x, float y)
        {
            ker.x = x;
            ker.y = y;
        }
        vector2f()
        {
            ker.x = 0;
            ker.y = 0;
        }

        const kernel getKer() const
        {
            return ker;
        }

        vector2f rotate(float angle) const
        {
            vector2f res;
            res.ker.x = ker.x * std::cos(angle) - ker.y * std::sin(angle);
            res.ker.y = ker.x * std::sin(angle) + ker.y * std::cos(angle);
            return res;
        }

        vector2f operator+(const vector2f &other) const
        {
            vector2f res(*this);
            res.ker.x += other.ker.x;
            res.ker.y += other.ker.y;
            return res;
        }

        vector2f operator-(const vector2f &other) const
        {
            vector2f res(*this);
            res.ker.x -= other.ker.x;
            res.ker.y -= other.ker.y;
            return res;
        }

        vector2f operator-() const
        {
            vector2f res(*this);
            res.ker.x *= -1;
            res.ker.y *= -1;
            return res;
        }

        vector2f operator*(double k) const
        {
            vector2f res(*this);
            res.ker.x *= k;
            res.ker.y *= k;
            return res;
        }

        bool operator==(const vector2f &other)
        {
            return (ker.x == other.ker.x && ker.y == other.ker.y);
        }

        friend std::ostream& operator<<(std::ostream &out, const vector2f &p)
        {
            out << "(" << p.ker.x << ", " << p.ker.y << ")";
            return out;
        }
        friend vector2f operator*(double k, const vector2f &v)
        {
            return v * k;
        }
    };

}

