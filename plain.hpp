#pragma once

#include <cstdint>
#include <cassert>

#include "color.hpp"
#include "line.hpp"
#include "vector.hpp"

namespace g {
    class plain
    {
    protected:
        int width;
        int height;

        color *pixels;

    public:
        plain(int w, int h, color c = color::black) : width(w), height(h)
        {
            pixels = new color[h * w];
            assert(pixels);
            for (int i = 0; i < h * w; ++i)
                pixels[i] = c;
        }

        ~plain()
        {
            assert(pixels);
            delete[] pixels;
            height = -1;
            width = -1;
        }

        int getHeight() const
        {
            return height;
        }

        int getWidth() const
        {
            return width;
        }

        inline const color operator()(int x, int y) const {
            assert(pixels);
            assert(y < height && x < width);
            return pixels[y * width + x];
        }

        inline color& operator()(int x, int y) {
            assert(pixels);
            assert(y < height && x < width);
            return pixels[y * width + x];
        }

        virtual void render() = 0;      // Non-const because GUI lib may change its own fields.

        void draw(int x0, int y0, const vector &v, color col)
        {
            assert(y0 < height && x0 < width);
            line l(x0, y0, v, 2);
            draw(l, col);
            vector ort(-v.getKer().y, v.getKer().x);
            vector arr1 = ( ort - v * 1.6) * 0.1;
            vector arr2 = (-ort - v * 1.6) * 0.1;
            draw(line(l.getKer().x2, l.getKer().y2, arr1, 2), col);
            draw(line(l.getKer().x2, l.getKer().y2, arr2, 2), col);
        }

        void draw(const line &l, color col)
        {
            auto ker = l.getKer();
            if (ker.y1 == ker.y2) {
                for (int x = std::min(ker.x1, ker.x2); x <= std::max(ker.x1, ker.x2); ++x) {
                    for (int y = std::max(ker.y1 - ker.w, 0); y <= std::min(ker.y1 + ker.w, height - 1); ++y) {
                        (*this)(x, y) = col;
                    }
                }
                return;
            }
            if (ker.x1 == ker.x2) {
                for (int y = std::min(ker.y1, ker.y2); y <= std::max(ker.y1, ker.y2); ++y) {
                    for (int x = std::max(ker.x1 - ker.w, 0); x <= std::min(ker.x1 + ker.w, width - 1); ++x) {
                        (*this)(x, y) = col;
                    }
                }
                return;
            }

            int begX = std::max(std::min(ker.x1, ker.x2) - ker.w, 0);
            int endX = std::min(std::max(ker.x1, ker.x2) + ker.w, width);

            int begY = std::max(std::min(ker.y1, ker.y2) - ker.w, 0);
            int endY = std::min(std::max(ker.y1, ker.y2) + ker.w, height);

            int a = ker.y1 - ker.y2;
            int b = ker.x2 - ker.x1;
            int c = ker.x1 * ker.y2 - ker.x2 * ker.y1;

            for (int x = begX; x < endX; ++x) {
                for (int y = begY; y < endY; ++y) {
                    double d = (a * x + b * y + c);
                    d *= d;
                    d /= (a*a + b*b);
                    double delta = ker.w * ker.w;
                    if (d < delta)
                        (*this)(x, y) = col;
                }
            }
        }
    };
}
