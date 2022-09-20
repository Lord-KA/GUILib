#pragma once

#include <string>
#include <cassert>

#include "color.hpp"
#include "line.hpp"

namespace g {
    class event {
    public:
        enum type_t {
            None = 0,
            Unsupported,
            MousePress,
            MouseRelease,
        };

        type_t type;
        g::vector pos;

        event(type_t t, g::vector p = g::vector(0, 0)) : type(t), pos(p) {};
        event& operator=(const event &other)
        {
            type = other.type;
            pos = other.pos;
            return *this;
        }
    };

    class windowAbstr {
    protected:
        int width;
        int height;

    public:
        virtual void drawLine(float x1, float y1, float x2, float y2, g::color c) = 0;
        virtual void drawLine(const g::line &l, g::color c) = 0;

        void drawVector(int x0, int y0, const vector &v, color col)
        {
            assert(y0 < height && x0 < width);
            line l(x0, y0, v);
            drawLine(l, col);
            vector ort(-v.getKer().y, v.getKer().x);
            vector arr1 = ( ort - v * 1.6) * 0.1;
            vector arr2 = (-ort - v * 1.6) * 0.1;
            drawLine(line(l.getKer().x2, l.getKer().y2, arr1, 2), col);
            drawLine(line(l.getKer().x2, l.getKer().y2, arr2, 2), col);
        }

        virtual void drawText(float x, float y, const std::string &text) = 0;
        virtual void setBackground(g::color c) = 0;
        virtual void update() = 0;
        virtual g::event getEvent() = 0;
    };
}
