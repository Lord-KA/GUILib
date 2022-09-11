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

        color *window;

    public:
        plain(uint64_t w, uint64_t h, color c = color::black) : width(w), height(h)
        {
            window = new color[h * w];
            assert(window);
            for (uint64_t i = 0; i < h * w; ++i)
                window[i] = c;
        }

        ~plain()
        {
            assert(window);
            delete[] window;
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
            assert(window);
            assert(i < height && j < width);
            return window[i * width + j];
        }

        inline color& operator()(uint64_t i, uint64_t j) {
            assert(window);
            assert(i < height && j < width);
            return window[i * width + j];
        }

        virtual void render() = 0;      // Non-const because GUI lib may change its own fields.
    };
}
