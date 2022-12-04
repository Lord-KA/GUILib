#pragma once

#include "Widget.hpp"

namespace gGUI {

    class Slider : public Widget
    {
    private:
        void moveHandler(Event ev)
        {
            std::cerr << "Slider moved at (" << ev.pos.ker.x << ", " << ev.pos.ker.y << ")!\n";   //FIXME
            double ratio = static_cast<double>(ev.pos.ker.x) / w;
            cur = min + (max - min) * ratio;
            size_t new_w = ev.pos.ker.x;
            size_t f = (w + h) / 2 * 0.05;
            new_w = std::max(new_w, f);
            new_w = std::min(new_w, w - 2 * f);
            pointer->resize(new_w, h - 2 * f);
        }

        Button *pointer = nullptr;
    public:
        Slot moveSlider = Slot(this, SLOT_FUNC(Slider::moveHandler));
        Signal moved;
        const int min;
        const int max;
        int cur;

        Slider(size_t x, size_t y, size_t w, size_t h, Widget *p, int min, int max, int cur, std::string bodyT = "darkgraypanel", std::string pointerT = "graypanel")
            : Widget(x, y, w, h, p, bodyT), min(min), max(max), cur(cur)
        {
            pointer = new Button(this, pointerT);
            resize(w, h);
            //TODO add label with cur
        }

        virtual void postload() override
        {
            moved.connect(moveSlider);
            Widget::postload();
        }

        void setLabel(char *text)
        {
            //TODO
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

        void emitSignals(Event ev) override
        {
            ev.widgetID = (uint64_t)this;
            if (ev.type == Event::MousePress) {
                moveHandler(ev);
                ev.curSlider = cur;
                std::cerr << "cur: " << cur << "\n";
                moved.call(ev);
            }
        }

        virtual void resize(size_t new_w, size_t new_h) override
        {
            //TODO do a proper resize.
            Widget::resize(new_w, new_h);
            size_t f = (w + h) / 2 * 0.05;
            pointer->move(f, f);
            assert(2 * f < h and 2 * f < w);
            pointer->resize(w - 2 * f, h - 2 * f);
        }
    };
}
