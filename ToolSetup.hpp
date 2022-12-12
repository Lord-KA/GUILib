#pragma once

#include "Widget.hpp"

namespace gGUI {
    class ToolSetup : public Widget {
    public:
        ToolSetup(size_t x, size_t y, size_t w, size_t h, Widget *p);
        uint64_t addButton(size_t x, size_t y, size_t w, size_t h, const char *text);
        uint64_t addLabel(size_t x, size_t y, size_t w, size_t h, const char *text);
        uint64_t addSlider(size_t x, size_t y, size_t w, size_t h, long min, long max, long cur);
        uint64_t addCanvas(size_t x, size_t y, size_t w, size_t h);
    };
}
