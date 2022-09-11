#pragma once

#include <iostream>
#include <cmath>

namespace g {

    class vector {
    private:
        class kernel {
        public:
            int x;
            int y;

        } ker;

    public:
        vector(const vector &other) : ker(other.ker) {}
        vector(int x, int y)
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
            ker.x = -1;
            ker.y = -1;
        }

        const kernel getKer() const
        {
            return ker;
        }

        vector operator+(const vector &other) const
        {
            vector res(*this);
            res.ker.x += other.ker.x;
            res.ker.y += other.ker.y;
            return res;
        }

        vector operator-(const vector &other) const
        {
            vector res(*this);
            res.ker.x -= other.ker.x;
            res.ker.y -= other.ker.y;
            return res;
        }

        vector operator-() const
        {
            vector res(*this);
            res.ker.x *= -1;
            res.ker.y *= -1;
            return res;
        }



        vector operator*(double k) const
        {
            vector res(*this);
            res.ker.x *= k;
            res.ker.y *= k;
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
        friend vector operator*(double k, const vector &v)
        {
            return v * k;
        }
    };

}

