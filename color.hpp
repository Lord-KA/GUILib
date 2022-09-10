#pragma once

#include <cstdint>

namespace g {
    class color
    {
    private:
        uint8_t r;
        uint8_t g;
        uint8_t b;
    public:
        enum preset {
            black = 0,
            gray,
            red,
            blue,
            green,
            white,
        };

        color() : r(0), g(0), b(0) {}
        color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

        color(const preset &p)
        {
            switch (p) {

            case black:
                r = 0;
                g = 0;
                b = 0;
                break;

            case gray:
                r = 128;
                g = 128;
                b = 128;
                break;

            case red:
                r = 255;
                g = 0;
                b = 0;
                break;

            case blue:
                r = 0;
                g = 0;
                b = 255;
                break;

            case green:
                r = 0;
                g = 255;
                b = 0;
                break;

            case white:
                r = 255;
                g = 255;
                b = 255;
                break;
            }
        }
        bool operator==(const color other)
        {
            return (r == other.r && g == other.g && b == other.b);
        }
    };
}