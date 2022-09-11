#pragma once

#include <cstdint>
#include <cassert>

#include "color.hpp"

namespace g {
    class plain
    {
    private:
        uint64_t h;
        uint64_t w;

        color *window;

    public:
        plain(uint64_t h, uint64_t w, color c = color::black) : h(h), w(w)
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
            h = -1;
            w = -1;
        }

        uint64_t getHeight() const
        {
            return h;
        }

        uint64_t getWidth() const
        {
            return w;
        }

        inline const color operator()(uint64_t i, uint64_t j) const {
            assert(window);
            assert(i < h && j < w);
            return window[i * w + j];
        }

        inline color& operator()(uint64_t i, uint64_t j) {
            assert(window);
            assert(i < h && j < w);
            return window[i * w + j];
        }

        virtual void render() const;
    };
}
