#pragma once

#include "Widget.hpp"
#include "ToolSetup.hpp"
#include "MainWindow.hpp"
#include "Button.hpp"

#include "tools.hpp"

namespace gGUI {
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
        Slot SetupTool  = Slot(this, SLOT_FUNC(ToolPalette::setupToolHandler));

        ToolPalette(size_t x, size_t y, size_t w_cnt, size_t h_cnt, size_t d, MainWindow *p)
            : Widget(x, y, w_cnt * d, h_cnt * d, p, "graypanel"),
              w_cnt(w_cnt), h_cnt(h_cnt), d(d), parent(p)
        {
            assert(parent);
            p->setToolPalette(this);
        }

        virtual void add_child(Widget *ch) override
        {
            assert(ch != nullptr);
            size_t pos = children.size();
            assert(pos + 1 < w_cnt * h_cnt);
            size_t h_pos = pos / w_cnt;
            size_t w_pos = pos % w_cnt;
            children.push_back(ch);
            ch->setParent(this);
            ch->move(w_pos * d, h_pos * d);
            ch->resize(d, d);
        }

        void selectToolHandler(Event ev)
        {
            parent->setToolSetup(toolSetups[ev.buttonID]);
        }

        void canvasMHandler(Event ev)
        {
            //TODO maybe check event type?
            //TODO traslate events
            booba::Event *bev = nullptr;
            tools[ev.buttonID]->apply(reinterpret_cast<booba::Image*>(parent->getCanvas()), bev);
        }

        void setupToolHandler(Event ev)
        {
            //TODO traslate events
            booba::Event *bev = nullptr;
            tools[ev.buttonID]->apply(reinterpret_cast<booba::Image*>(parent->getCanvas()), bev);
        }

        void setToolSetupPos(size_t x, size_t y, size_t w, size_t h)
        {
            ts_x = x;
            ts_y = y;
            ts_w = w;
            ts_h = h;
        }

        void regButton(uint64_t buttonID)
        {
            tools[buttonID] = curTool;
        }

        void addTool(booba::Tool *tool)
        {
            if (ts_x == -1 || ts_y == -1 || ts_w == -1 || ts_h == -1)
                assert(!"You need to set ToolSetup position first");
            Button *b = new Button(this, tool->getTexture());
            assert(b);
            b->clicked.connect(SelectTool);
            auto *ts = new ToolSetup(ts_x, ts_y, ts_w, ts_h, parent);
            assert(ts);
            ts->hide();
            toolSetups[(uint64_t)b] = ts;
            curTool = tool;
            std::cerr << "ToolPalette: id = " << (uint64_t)b << "\n";
            tools[(uint64_t)b] = tool;
            parent->setToolSetup(ts);
            tool->buildSetupWidget();
        }
    };
}
