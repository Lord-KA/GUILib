#pragma once

#include "ToolSetup.hpp"
#include "ToolPalette.hpp"
#include "MainWindow.hpp"
#include "Button.hpp"
#include "Slider.hpp"

namespace gGUI {
    ToolSetup::ToolSetup(size_t x, size_t y, size_t w, size_t h, Widget *p)
        : Widget(x, y, w, h, p, "graypanel") {}

    uint64_t ToolSetup::addButton(size_t x, size_t y, size_t w, size_t h, const char *text)
    {
        auto *b = new Button(x, y, w, h, this, text);
        auto *palette = dynamic_cast<MainWindow*>(parent)->getToolPalette();
        b->clicked.connect(palette->SetupToolB);
        palette->regButton((uint64_t)b);
        return (uint64_t)b;
    }

    uint64_t ToolSetup::addLabel(size_t x, size_t y, size_t w, size_t h, const char *text)
    {
        return (uint64_t)(new Label(x, y, w, h, this, text));
    }

    uint64_t ToolSetup::addSlider(size_t x, size_t y, size_t w, size_t h, size_t max, size_t cur)
    {
        auto *s = new Slider(x, y, w, h, this, 0, max, cur);
        auto *palette = dynamic_cast<MainWindow*>(parent)->getToolPalette();
        s->moved.connect(palette->SetupToolS);
        palette->regButton((uint64_t)s);
        return (uint64_t)s;
    }
}
