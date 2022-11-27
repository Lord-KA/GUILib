#pragma once

#include <vector>
#include <functional>
#include <cassert>

#include "vector2f.hpp"

#define SLOT_FUNC(macro_func) (static_cast<handler_t>(&macro_func))

namespace gGUI {

    class Widget;

    class Event {
    public:
        enum type_t {
            None = 0,
            Unsupported,
            MousePress,
            MouseRelease,
            MouseMoved,
        };

        type_t type;
        g::vector2f pos;
        g::vector2f prev;
        uint64_t buttonID;

        Event(type_t t, g::vector2f pos = {0, 0}, g::vector2f prev = {0, 0}) : type(t), pos(pos), prev(prev) {}
        Event& operator=(const Event &other)
        {
            type = other.type;
            pos = other.pos;
            return *this;
        }
    };

    struct Signal;

    typedef void (Widget::*handler_t)(Event);

    struct Slot {
        Widget *widget = NULL;
        handler_t handler;
        //std::function<void(Widget&, Event)> handler;
        std::vector<Signal*> signals;
        void disconnect(Signal &sig);
        Slot() : widget(nullptr), handler(nullptr) {}
        Slot(Widget *w, handler_t h) : widget(w), handler(h) {}
        ~Slot();
    };

    struct Signal {
        std::vector<Slot*> slots;
        void connect(Slot &slt);
        void disconnect(Slot &slt);
        void call(Event ev);
        ~Signal();
    };

    /*  //TODO
    class EventManager {
    private:
        std::vector<Signal> signals;
    };
    */
}
