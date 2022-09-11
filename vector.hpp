#pragma once

#include <iostream>
#include <cmath>

namespace g {

    class vector {
    private:
        class kernel {
        public:
            size_t x;
            size_t y;

        } ker;

    public:
        vector(const vector &other) : ker(other.ker) {}
        vector(size_t x, size_t y)
        {
            ker.x = x;
            ker.y = y;
        }
        vector()
        {
            ker.x = 0;
            ker.y = 0;
        }

        ~vector()
        {
            ker.x = NAN;
            ker.y = NAN;
        }

        const kernel getKer() const
        {
            return ker;
        }

        vector operator+(const vector &other)
        {
            vector res(other);
            res.ker.x += ker.x;
            res.ker.y += ker.y;
            return res;
        }

        vector operator-(const vector &other)
        {
            vector res(other);
            res.ker.x -= ker.x;
            res.ker.y -= ker.y;
            return res;
        }

        vector operator*(size_t n)
        {
            vector res(*this);
            res.ker.x *= n;
            res.ker.y *= n;
            return res;
        }

        vector& operator=(const vector &other)
        {
            ker.x += other.ker.x;
            ker.y += other.ker.y;
            return *this;
        }

        bool operator==(const vector &other)
        {
            return (ker.x == other.ker.x && ker.y == other.ker.y);
        }

        friend std::ostream& operator<<(std::ostream &out, const vector &p)
        {
            out << "(" << p.ker.x << ", " << p.ker.y << ")";
            return out;
        }
    };

}
