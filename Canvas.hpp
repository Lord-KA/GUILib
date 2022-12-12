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
        bool modified = true;
        sf::Image image;
        sf::Texture texture;

    public:
        Signal MouseAct;

        Canvas(size_t in_x, size_t in_y, size_t in_w, size_t in_h, MainWindow *p, g::color c = g::color::white)
            : Widget(in_x, in_y, in_w, in_h, p, "NONE")
        {
            assert(parent);
            p->setCanvas(this);
            image.create(w, h, sf::Color(c.toInt()));

            MouseAct.connect(dynamic_cast<MainWindow*>(parent)->getToolPalette()->CanvasMAct);
        }

        Canvas(size_t in_x, size_t in_y, size_t in_w, size_t in_h, Widget *p, g::color c = g::color::white)
            : Widget(in_x, in_y, in_w, in_h, p, "NONE")
        {
            assert(parent);
            image.create(w, h, sf::Color(c.toInt()));
        }

        virtual size_t getH() override
        {
            return h;
        }

        virtual size_t getW() override
        {
            return w;
        }

        virtual void emitSignals(Event ev)
        {
            ev.widgetID = reinterpret_cast<uint64_t>(this);
            if (ev.type == Event::MouseMove || ev.type == Event::MousePress || ev.type == Event::MouseRelease) {
                MouseAct.call(ev);
            }
        }

        virtual color getPixel(size_t in_x, size_t in_y) override
        {
            assert(0 <= in_x and in_x < w and 0 <= in_y and in_y < h);
            return image.getPixel(in_x, in_y).toInteger();
        }

        virtual void setPixel(size_t in_x, size_t in_y, color c) override
        {
            assert(in_x < w and in_y < h);
            image.setPixel(in_x, in_y, sf::Color(c));
            modified = true;
        }

        void clear(color c)
        {
            image.create(w, h, sf::Color(c));
        }

        virtual void draw(sf::RenderWindow &window, size_t p_x, size_t p_y)
        {
            if (not isShown)
                return;
            if (modified) {
                texture.loadFromImage(image);
                sprite.setTexture(texture);
                modified = false;
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
