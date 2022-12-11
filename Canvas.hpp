#pragma once

#include "Widget.hpp"
#include "MainWindow.hpp"
#include "ToolPalette.hpp"
#include "color.hpp"

#include <SFML/Graphics.hpp>

#include "tools.hpp"

namespace gGUI {

    class Canvas : public Widget, public booba::Image {
    using color = uint32_t;
    protected:
        color *pixels = nullptr;
        bool modified = true;
        bool usedArr = false;
        sf::Image image;
        sf::Texture texture;

    public:
        Signal MouseAct;

        Canvas(size_t in_x, size_t in_y, size_t in_w, size_t in_h, MainWindow *p, g::color c = g::color::white)
            : Widget(in_x, in_y, in_w, in_h, p, "NONE")
        {
            assert(parent);
            p->setCanvas(this);
            pixels = new color[w * h];
            assert(pixels != nullptr);
            image.create(w, h, sf::Color(c.toInt()));

            MouseAct.connect(dynamic_cast<MainWindow*>(parent)->getToolPalette()->CanvasMAct);
        }

        Canvas(size_t in_x, size_t in_y, size_t in_w, size_t in_h, Widget *p, g::color c = g::color::white)
            : Widget(in_x, in_y, in_w, in_h, p, "NONE")
        {
            assert(parent);
            pixels = new color[w * h];
            assert(pixels != nullptr);
            image.create(w, h, sf::Color(c.toInt()));
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

        virtual void emitSignals(Event ev)
        {
            ev.widgetID = reinterpret_cast<uint64_t>(this);
            if (ev.type == Event::MouseMove || ev.type == Event::MousePress || ev.type == Event::MouseRelease) {
                MouseAct.call(ev);
            }
            /*
            auto p = dynamic_cast<MainWindow*>(parent)->getToolPalette();
            p->emitSignals(ev);
            */
        }

        virtual color getPixel(int32_t in_x, int32_t in_y) override    //FIXME change to size_t when standart allowes
        {
            assert(0 <= in_x and in_x < w and 0 <= in_y and in_y < h);
            return pixels[in_y * w + in_x];
        }

        virtual void putPixel(uint32_t in_x, uint32_t in_y, color c) override
        {
            assert(in_x < w and in_y < h);
            if (pixels[in_y * w + in_x] == c)
                return;
            pixels[in_y * w + in_x] = c;
            image.setPixel(in_x, in_y, sf::Color(c));
            modified = true;
        }

        virtual color& operator()(uint32_t in_x, uint32_t in_y)
        {
            assert(in_x < w and in_y < h);
            modified = true;
            usedArr = true;
            return pixels[in_y * w + in_x];
        }

        virtual const color& operator()(uint32_t in_x, uint32_t in_y) const
        {
            assert(in_x < w and in_y < h);
            return pixels[in_y * w + in_x];
        }

        virtual void draw(sf::RenderWindow &window, size_t p_x, size_t p_y)
        {
            if (not isShown)
                return;
            if (modified) {
                assert(pixels != nullptr);
                if (usedArr)
                    image.create(w, h, (uint8_t*)pixels);
                texture.loadFromImage(image);
                sprite.setTexture(texture);
                modified = false;
                usedArr = false;
            }
            Widget::draw(window, p_x, p_y);
        }

        virtual Widget *belongs(size_t pos_x, size_t pos_y, size_t parent_x = 0, size_t parent_y = 0) const override
        {
            if (not isShown)
                return nullptr;
            if ((pos_x <= x + parent_x) || (pos_y <= y + parent_y)
                    || (w <= pos_x - x - parent_x) || (h <= pos_y - y - parent_y))
                return nullptr;
            return (Widget*)this;
        }
    };
}
