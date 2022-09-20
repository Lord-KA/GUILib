#pragma once

#include <iostream>
#include <cmath>
#include <cassert>

namespace g {

    class vector3f {
    private:
        class kernel {
        public:
            float x;
            float y;
            float z;

        } ker;

    public:
        vector3f(const vector3f &other) : ker(other.ker) {}
        vector3f(int x, int y, int z)
        {
            ker.x = x;
            ker.y = y;
            ker.z = z;
        }
        vector3f()
        {
            ker.x = 0;
            ker.y = 0;
            ker.z = 0;
        }

        ~vector3f()
        {
            ker.x = -1;
            ker.y = -1;
            ker.z = -1;
        }

        const kernel getKer() const
        {
            return ker;
        }

        vector3f rotate(float angle) const
        {
            assert(!"Not implemented yet!");
            vector3f res;
            res.ker.x = ker.x * std::cos(angle) - ker.y * std::sin(angle);
            res.ker.y = ker.x * std::sin(angle) + ker.y * std::cos(angle);
            res.ker.z = ker.z * std::sin(angle) + ker.z * std::cos(angle);
            return res;
        }

        vector3f operator+(const vector3f &other) const
        {
            vector3f res(*this);
            res.ker.x += other.ker.x;
            res.ker.y += other.ker.y;
            res.ker.z += other.ker.z;
            return res;
        }

        vector3f operator-(const vector3f &other) const
        {
            vector3f res(*this);
            res.ker.x -= other.ker.x;
            res.ker.y -= other.ker.y;
            res.ker.z -= other.ker.z;
            return res;
        }

        vector3f operator-() const
        {
            vector3f res(*this);
            res.ker.x *= -1;
            res.ker.y *= -1;
            res.ker.z *= -1;
            return res;
        }

        vector3f operator*(float k) const
        {
            vector3f res(*this);
            res.ker.x *= k;
            res.ker.y *= k;
            res.ker.z *= k;
            return res;
        }

        vector3f operator/(float k) const
        {
            vector3f res(*this);
            res.ker.x /= k;
            res.ker.y /= k;
            res.ker.z /= k;
            return res;
        }

        vector3f& operator=(const vector3f &other)
        {
            ker.x = other.ker.x;
            ker.y = other.ker.y;
            ker.z = other.ker.z;
            return *this;
        }

        float dot(const vector3f other) const
        {
            return ker.x * other.ker.x + ker.y * other.ker.y + ker.z * other.ker.z;
        }

        void rotY(float a)
        {
            ker.x =  std::cos(a) * ker.x + std::sin(a) * ker.z;
            ker.z = -std::sin(a) * ker.x + std::cos(a) * ker.z;
        }

        void rotX(float a)
        {
            ker.y = std::cos(a) * ker.y - std::sin(a) * ker.z;
            ker.z = std::sin(a) * ker.y + std::cos(a) * ker.z;
        }

        void rotZ(float a)
        {
            ker.x = std::cos(a) * ker.x - std::sin(a) * ker.y;
            ker.y = std::sin(a) * ker.x + std::cos(a) * ker.y;
        }

        vector3f normalize() const
        {
            float d = std::sqrt(dot(*this));
            return (*this) / d;
        }

        bool operator==(const vector3f &other)
        {
            return (ker.x == other.ker.x && ker.y == other.ker.y && ker.z == other.ker.z);
        }

        friend std::ostream& operator<<(std::ostream &out, const vector3f &p)
        {
            out << "(" << p.ker.x << ", " << p.ker.y << ", " << p.ker.z << ")";
            return out;
        }
        friend vector3f operator*(double k, const vector3f &v)
        {
            return v * k;
        }
    };

}

