#include <iostream>
#include <cassert>

#include "MainWindow.hpp"
#include "ToolSetup.hpp"
#include "Canvas.hpp"

#include "tools.hpp"

namespace booba {
    gGUI::MainWindow *MAINWINDOW = nullptr;
    ApplicationContext *APPCONTEXT = nullptr;

    uint64_t createButton(size_t x, size_t y, size_t w, size_t h, const char *text)
    {
        assert(MAINWINDOW);
        return MAINWINDOW->getToolSetup()->addButton(x, y, w, h, text);
    }

    uint64_t createLabel(size_t x, size_t y, size_t w, size_t h, const char *text)
    {
        assert(MAINWINDOW);
        return MAINWINDOW->getToolSetup()->addLabel(x, y, w, h, text);
    }

    uint64_t createSlider(size_t x, size_t y, size_t w, size_t h, long min, long max, long start)
    {
        assert(MAINWINDOW);
        return MAINWINDOW->getToolSetup()->addSlider(x, y, w, h, min, max, start);
    }

    uint64_t createCanvas(size_t x, size_t y, size_t w, size_t h)    //FIXME rename after v3.0.0 standart release
    {
        assert(MAINWINDOW);
        return MAINWINDOW->getToolSetup()->addCanvas(x, y, w, h);
    }

    void putPixel (uint64_t canvas, size_t x, size_t y, uint32_t color)
    {
        gGUI::Canvas *c = reinterpret_cast<gGUI::Canvas*>(canvas);
        c->setPixel(x, y, color);
    }

    void putSprite(uint64_t canvas, size_t x, size_t y, size_t w, size_t h, const char* texture)
    {
        assert(!"no sprites for canvas yet");
    }

    GUID getGUID()
    {
        assert(!"no GUID yet");
    }

    bool setToolBarSize(size_t w, size_t h)
    {
        if (w > 1000 or h > 600)
            return false;
        MAINWINDOW->getToolPalette()->setToolSetupPos(-1, -1, w, h);
        return true;
    }

    void cleanCanvas(uint64_t canvasId, uint32_t color)
    {
        gGUI::Canvas *c = reinterpret_cast<gGUI::Canvas*>(canvasId);
        c->clear(color);
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
