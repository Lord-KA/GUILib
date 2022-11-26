#pragma once

#include "Widget.hpp"
#include "color.hpp"

#include <SFML/Graphics.hpp>

#include "tools.hpp"

namespace gGUI {

    class Canvas : public Widget, public booba::Image {
    using color = uint32_t;
    protected:
        color *pixels = nullptr;
        bool modified = true;

    public:
        Canvas(size_t in_x, size_t in_y, size_t in_w, size_t in_h, Widget *p, g::color c = g::color::white)
            : Widget(in_x, in_y, in_w, in_h, p, "NONE")
        {
            pixels = new color[w * h];
            assert(pixels != nullptr);
        }

        ~Canvas()
        {
            assert(pixels != nullptr);
            delete[] pixels;
        }

        virtual uint32_t getH() override
        {
            return h;
        }

        virtual uint32_t getW() override
        {
            return w;
        }

        virtual color getPixel(int32_t x, int32_t y) override    //FIXME change to size_t when standart allowes
        {
            assert(0 <= x and x < w and 0 <= y and y < h);
            return pixels[y * w + x];
        }

        virtual void putPixel(uint32_t x, uint32_t y, color c) override
        {
            assert(x < w and y < h);
            if (pixels[y * w + x] == c)
                return;
            pixels[y * w + x] = c;
            modified = true;
        }

        virtual color& operator()(uint32_t x, uint32_t y)
        {
            assert(x < w and y < h);
            modified = true;
            return pixels[y * w + x];
        }

        virtual const color& operator()(uint32_t x, uint32_t y) const
        {
            assert(x < w and y < h);
            return pixels[y * w + x];
        }

        virtual void draw(sf::RenderWindow &window, size_t p_x, size_t p_y)
        {
            if (not isShown)
                return;
            if (modified) {
                assert(pixels != nullptr);
                sf::Image image;
                image.create(w, h, (uint8_t*)pixels);
                sf::Texture texture;
                texture.loadFromImage(image);
                sprite.setTexture(texture);
                modified = false;
            }
            Widget::draw(window, p_x, p_y);
        }
    };
}
