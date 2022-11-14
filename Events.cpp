#include "Events.hpp"

namespace gGUI {
    void Slot::disconnect(Signal &sig)
    {
        auto it = signals.begin();
        while (it != signals.end() and *it != &sig)
            ++it;
        if (it != signals.end())
            signals.erase(it);
    }

    Slot::~Slot()
    {
        for (auto sig : signals)
            sig->disconnect(*this);
    }

    void Signal::connect(Slot &slt)
    {
        slots.push_back(&slt);
        slt.signals.push_back(this);
    }

    void Signal::disconnect(Slot &slt)
    {
        auto it = slots.begin();
        while (it != slots.end() and *it != &slt)
            ++it;
        if (it != slots.end())
            slots.erase(it);
    }

    void Signal::call(Event ev)
    {
        for (auto elem : slots) {
            assert(elem->widget);
            ((elem->widget)->*(elem->handler))(ev);
        }
    }

    Signal::~Signal()
    {
        for (auto slt : slots)
            slt->disconnect(*this);
    }
}
