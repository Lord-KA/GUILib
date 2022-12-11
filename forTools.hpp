#include <iostream>
#include <cassert>

#include "MainWindow.hpp"
#include "ToolSetup.hpp"
#include "Canvas.hpp"

#include "tools.hpp"

namespace booba {
    gGUI::MainWindow *MAINWINDOW = nullptr;
    ApplicationContext *APPCONTEXT = nullptr;

    Image::~Image() {}

    uint64_t createButton(int32_t x, int32_t y, uint32_t w, uint32_t h, const char *text)
    {
        assert(MAINWINDOW);
        return MAINWINDOW->getToolSetup()->addButton(x, y, w, h, text);
    }

    uint64_t createLabel(int32_t x, int32_t y, uint32_t w, uint32_t h, const char *text)
    {
        assert(MAINWINDOW);
        return MAINWINDOW->getToolSetup()->addLabel(x, y, w, h, text);
    }

    uint64_t createScrollbar(int32_t x, int32_t y, uint32_t w, uint32_t h, int32_t max, int32_t start)    //FIXME rename to `slider` after v2.0.0 standart release
    {
        assert(MAINWINDOW);
        return MAINWINDOW->getToolSetup()->addSlider(x, y, w, h, max, start);
    }

    uint64_t createCanvas(int32_t x, int32_t y, int32_t w, int32_t h)    //FIXME rename after v2.0.0 standart release
    {
        assert(MAINWINDOW);
        return MAINWINDOW->getToolSetup()->addCanvas(x, y, w, h);
    }

    void putPixel (uint64_t canvas, int32_t x, int32_t y, uint32_t color)
    {
        gGUI::Canvas *c = reinterpret_cast<gGUI::Canvas*>(canvas);
        c->putPixel(x, y, color);
    }

    void putSprite(uint64_t canvas, int32_t x, int32_t y, uint32_t w, uint32_t h, const char* texture)
    {
        assert(!"no sprites for canvas yet");
    }

    void addTool(Tool* tool)
    {
        MAINWINDOW->getToolPalette()->addTool(tool);
    }

    void addFilter(Tool* tool)
    {
        addTool(tool);
    }
}
