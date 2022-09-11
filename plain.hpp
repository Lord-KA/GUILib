#pragma once

#include <cstdint>
#include <cassert>

#include "color.hpp"

namespace g {
    class plain
    {
    protected:
        uint64_t width;
        uint64_t height;

        color *pixels;

    public:
        plain(uint64_t w, uint64_t h, color c = color::black) : width(w), height(h)
        {
            pixels = new color[h * w];
            assert(pixels);
            for (uint64_t i = 0; i < h * w; ++i)
                pixels[i] = c;
        }

        ~plain()
        {
            assert(pixels);
            delete[] pixels;
            height = -1;
            width = -1;
        }

        uint64_t getHeight() const
        {
            return height;
        }

        uint64_t getWidth() const
        {
            return width;
        }

        inline const color operator()(uint64_t i, uint64_t j) const {
            assert(pixels);
            assert(i < height && j < width);
            return pixels[i * width + j];
        }

        inline color& operator()(uint64_t i, uint64_t j) {
            assert(pixels);
            assert(i < height && j < width);
            return pixels[i * width + j];
        }

        virtual void render() = 0;      // Non-const because GUI lib may change its own fields.
    };
}
