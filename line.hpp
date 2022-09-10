#pragma once

#include <iostream>
#include <climits>

namespace g {

class line {
private:
    class kernel {
    public:
        long x;
        long y;
    } ker;

public:
    line(const line &other) : ker(other.ker) {}
    line(long x, long y)
    {
        ker.x = x;
        ker.y = y;
    }
    line()
    {
        ker.x = 0;
        ker.y = 0;
    }

    ~line()
    {
        ker.x = LLONG_MAX;
        ker.y = LLONG_MAX;
    }

    line operator+(const line &other)
    {
        line res(other);
        res.ker.x += ker.x;
        res.ker.y += ker.y;
        return res;
    }

    line operator-(const line &other)
    {
        line res(other);
        res.ker.x -= ker.x;
        res.ker.y -= ker.y;
        return res;
    }

    line operator*(long n)
    {
        line res(*this);
        res.ker.x *= n;
        res.ker.y *= n;
        return res;
    }

    line& operator=(const line &other)
    {
        ker.x += other.ker.x;
        ker.y += other.ker.y;
        return *this;
    }

    bool operator==(const line &other)
    {
        return (ker.x == other.ker.x && ker.y == other.ker.y);
    }

    friend std::ostream& operator<<(std::ostream &out, const line &p)
    {
        out << "(" << p.ker.x << ", " << p.ker.y << ")";
        return out;
    }
};

}
