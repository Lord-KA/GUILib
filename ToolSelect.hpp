#pragma once

#include "Widget.hpp"

namespace gGUI {

    class ToolSelect : public Widget {
    private:
        size_t w_cnt = 0;
        size_t h_cnt = 0;
        size_t d = 0;

    public:
        ToolSelect(size_t x, size_t y, size_t w_cnt, size_t h_cnt, size_t d, MainWindow *p)
            : Widget(x, y, w_cnt * d, h_cnt * d, p, "buttonbg"),
              w_cnt(w_cnt), h_cnt(h_cnt), d(d) {}

        virtual void add_child(Widget *ch) override
        {
            assert(ch != nullptr);
            size_t pos = children.size();
            assert(pos + 1 < w_cnt * h_cnt);
            size_t h_pos = pos / w_cnt;
            size_t w_pos = pos % w_cnt;
            children.push_back(ch);
            std::cerr << "w_pos = " << w_pos << "\n";
            ch->setParent(this);
            ch->move(w_pos * d, h_pos * d);
            ch->resize(d, d);
        }
    };
}
