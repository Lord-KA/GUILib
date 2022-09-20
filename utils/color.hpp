#pragma once

#include <cstdint>
#include <iostream>

namespace g {
    class color
    {
    private:
        uint8_t r;
        uint8_t g;
        uint8_t b;

    public:
        enum preset {
            black   = 0x000000,
            gray    = 0x808080,
            red     = 0xff0000,
            green   = 0x00ff00,
            blue    = 0x0000ff,
            white   = 0xffffff,
            yellow  = 0xffff00,
        };

        color() : r(0), g(0), b(0) {}
        color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
        color(int n)
        {
            r = (0xff0000 & n) / 0x10000;
            g = (0x00ff00 & n) / 0x100;
            b = 0x0000ff & n;
        }

        uint8_t getR() const
        {
            return r;
        }

        uint8_t getG() const
        {
            return g;
        }

        uint8_t getB() const
        {
            return b;
        }

        color operator*(float k) const
        {
            color res(*this);
            res.r *= k;
            res.g *= k;
            res.b *= k;
            return res;
        }

        bool operator==(const color other)
        {
            return (r == other.r && g == other.g && b == other.b);
        }

        friend std::ostream& operator<<(std::ostream &out, const color &c)
        {
            out << "(" << (int)c.r << ", " << (int)c.g << ", " << (int)c.b << ")";
            return out;
        }
    };
}
