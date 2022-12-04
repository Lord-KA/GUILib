#pragma once

#include "Widget.hpp"

#include "tools.hpp"

namespace gGUI {
    class ToolSetup;
    class MainWindow;

    class ToolPalette : public Widget {
    private:
        size_t w_cnt = 0;
        size_t h_cnt = 0;
        size_t d = 0;

        size_t ts_x = -1;
        size_t ts_y = -1;
        size_t ts_w = -1;
        size_t ts_h = -1;

        std::map<uint64_t, ToolSetup*>   toolSetups;
        std::map<uint64_t, booba::Tool*> tools;

        booba::Tool* curTool = nullptr;

        MainWindow *parent;
    public:
        Slot SelectTool = Slot(this, SLOT_FUNC(ToolPalette::selectToolHandler));
        Slot CanvasMAct = Slot(this, SLOT_FUNC(ToolPalette::canvasMHandler));
        Slot SetupToolB  = Slot(this, SLOT_FUNC(ToolPalette::setupToolBHandler));
        Slot SetupToolS  = Slot(this, SLOT_FUNC(ToolPalette::setupToolSHandler));
        Slot SetupToolC  = Slot(this, SLOT_FUNC(ToolPalette::setupToolCHandler));

        ToolPalette(size_t x, size_t y, size_t w_cnt, size_t h_cnt, size_t d, MainWindow *p);

        virtual void add_child(Widget *ch) override;

        void selectToolHandler(Event ev);

        void canvasMHandler(Event ev);

        void setupToolBHandler(Event ev);
        void setupToolSHandler(Event ev);
        void setupToolCHandler(Event ev);

        void setToolSetupPos(size_t x, size_t y, size_t w, size_t h);

        void regButton(uint64_t widgetID);

        void addTool(booba::Tool *tool);
    };
}
