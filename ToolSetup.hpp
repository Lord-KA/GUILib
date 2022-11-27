#pragma once

#include "Widget.hpp"
#include "Button.hpp"

namespace gGUI {

    class ToolSetup : public Widget {
    public:
        ToolSetup(size_t x, size_t y, size_t w_cnt, size_t h_cnt, size_t d, MainWindow *p)
            : Widget(x, y, w_cnt * d, h_cnt * d, p, "graypanel") {}

        uint64_t addButton(size_t x, size_t y, size_t w, size_t h, const char *text)
        {
            //TODO connect Button signals
            return (uint64_t)(new Button(x, y, w, h, this, text));
        }

        uint64_t addLabel(size_t x, size_t y, size_t w, size_t h, const char *text)
        {
            return (uint64_t)(new Label(x, y, w, h, this, text));
        }

        uint64_t addSlider(size_t x, size_t y, size_t w, size_t h, size_t max, size_t cur)
        {
            assert(!"no slider yet");
            return 0;
        }
    };
}
