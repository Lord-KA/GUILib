#pragma once

#include <iostream>
#include <cmath>

namespace g {

    class vector2d {
    private:
        class kernel {
        public:
            int x;
            int y;

        } ker;

    public:
        vector2d(int x, int y)
        {
            ker.x = x;
            ker.y = y;
        }

        vector2d()
        {
            ker.x = 0;
            ker.y = 0;
        }

        const kernel getKer() const
        {
            return ker;
        }

        vector2d rotate(float angle) const
        {
            vector2d res;
            res.ker.x = ker.x * std::cos(angle) - ker.y * std::sin(angle);
            res.ker.y = ker.x * std::sin(angle) + ker.y * std::cos(angle);
            return res;
        }

        vector2d operator+(const vector2d &other) const
        {
            vector2d res(*this);
            res.ker.x += other.ker.x;
            res.ker.y += other.ker.y;
            return res;
        }

        vector2d operator-(const vector2d &other) const
        {
            vector2d res(*this);
            res.ker.x -= other.ker.x;
            res.ker.y -= other.ker.y;
            return res;
        }

        vector2d operator-() const
        {
            vector2d res(*this);
            res.ker.x *= -1;
            res.ker.y *= -1;
            return res;
        }

        vector2d operator*(double k) const
        {
            vector2d res(*this);
            res.ker.x *= k;
            res.ker.y *= k;
            return res;
        }

        bool operator==(const vector2d &other)
        {
            return (ker.x == other.ker.x && ker.y == other.ker.y);
        }

        friend std::ostream& operator<<(std::ostream &out, const vector2d &p)
        {
            out << "(" << p.ker.x << ", " << p.ker.y << ")";
            return out;
        }
        friend vector2d operator*(double k, const vector2d &v)
        {
            return v * k;
        }
    };
}

