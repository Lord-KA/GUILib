#pragma once

#include "Widget.hpp"
#include "Label.hpp"

namespace gGUI {

    class Button : public Widget
    {
    private:
        Slot press = Slot(this, SLOT_FUNC(Button::pressHandler));
        Slot release;
    public:
        Signal clicked;

        void pressHandler(Event ev)
        {
            std::cerr << "Button pressed at (" << ev.pos.ker.x << ", " << ev.pos.ker.y << ")!\n";   //FIXME
        }

        Button(size_t x, size_t y, size_t w, size_t h, Widget *p, char *str) : Widget(x, y, w, h, p, TextureManager::code::buttonbg)
        {
            clicked.connect(press);
            Label *text = new Label(10, 60, -1, h - 100, this, str);
            add_child(text);
        }

        bool handle(const Event ev)
        {
            if (ev.type == Event::MousePress) {
                clicked.call(ev);
            }
        }

        void emitSignals(Event ev) override
        {
            if (ev.type == Event::MousePress)
                clicked.call(ev);
        }
    };
}
