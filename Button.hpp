#pragma once

#include "Widget.hpp"
#include "Label.hpp"

namespace gGUI {

    class Button : public Widget
    {
    private:
        Slot press = Slot(this, SLOT_FUNC(Button::pressHandler));
        Slot release;
        Label *text = nullptr;
    public:
        Signal clicked;

        void pressHandler(Event ev)
        {
            std::cerr << "Button pressed at (" << ev.pos.ker.x << ", " << ev.pos.ker.y << ")!\n";   //FIXME
        }

        Button(size_t x, size_t y, size_t w, size_t h, Widget *p, const char *str, std::string t = "buttonbg")
            : Widget(x, y, w, h, p, t)
        {
            if (str != nullptr) {
                text = new Label(w, h, w, h, this, str);
                add_child(text);
            }
        }

        Button(Widget *p, std::string t = "buttonbg")
            : Widget(-1, -1, -1, -1, p, t) {}

        virtual void postload() override
        {
            clicked.connect(press);
            Widget::postload();
        }


        bool handle(const Event ev)
        {
            if (ev.type == Event::MousePress) {
                clicked.call(ev);
            }
        }

        void emitSignals(Event ev) override
        {
            ev.buttonID = (uint64_t)this;
            if (ev.type == Event::MousePress)
                clicked.call(ev);
        }

        virtual void resize(size_t new_w, size_t new_h) override
        {
            Widget::resize(new_w, new_h);
            text->resize(w, h);
        }
    };
}
