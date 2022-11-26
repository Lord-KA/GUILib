#pragma once

#include "MainWindow.hpp"

namespace gGUI {

    class TopBar : public Widget {

    public:
        TopBar(MainWindow *p, size_t h = 100) : Widget(0, 0, p->getWidth(), h, p, "panel") {}

        virtual void add_child(Widget *ch) override
        {
            assert(ch != nullptr);
            size_t w;
            if (not children.empty())
                w = children.back()->getX() + children.back()->getWidth();
            else
                w = x;
            children.push_back(ch);
            ch->setParent(this);
            ch->move(w, 0);
            ch->resize(-1, h);
        }
    };
}
