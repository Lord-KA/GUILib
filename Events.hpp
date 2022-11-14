#pragma once

#include <vector>
#include <functional>
#include <cassert>

// #include "Widget.hpp"
#include "vector2f.hpp"


namespace gGUI {

    class Widget;

    class Event {
    public:
        enum type_t {
            None = 0,
            Unsupported,
            MousePress,
            MouseRelease,
        };

        type_t type;
        g::vector2f pos;

        Event(type_t t, g::vector2f p = {0, 0}) : type(t), pos(p) {};
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
