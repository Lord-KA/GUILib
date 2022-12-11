#pragma once

#include "ToolPalette.hpp"
#include "ToolSetup.hpp"
#include "MainWindow.hpp"
#include "Button.hpp"
#include "Canvas.hpp"


namespace gGUI {
    ToolPalette::ToolPalette(size_t x, size_t y, size_t w_cnt, size_t h_cnt, size_t d, MainWindow *p)
        : Widget(x, y, w_cnt * d, h_cnt * d, p, "graypanel"),
          w_cnt(w_cnt), h_cnt(h_cnt), d(d), parent(p)
    {
        assert(parent);
        p->setToolPalette(this);
    }

    void ToolPalette::add_child(Widget *ch)
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

    void ToolPalette::selectToolHandler(Event ev)
    {
        parent->setToolSetup(toolSetups[ev.widgetID]);
    }

    void ToolPalette::canvasMHandler(Event ev)
    {
        auto tool = tools[(uint64_t)parent->getToolSetup()];
        if (not tool)
            return;

        booba::Event bev = {};
        if (ev.type == Event::MousePress) {
            bev.type = booba::EventType::MousePressed;
            bev.Oleg.mbedata.x = ev.pos.ker.x;
            bev.Oleg.mbedata.y = ev.pos.ker.y;
            bev.Oleg.mbedata.button = ev.leftButton ? booba::MouseButton::Left : booba::MouseButton::Right;
        } else if (ev.type == Event::MouseRelease) {
            bev.type = booba::EventType::MouseReleased;
            bev.Oleg.mbedata.x = ev.pos.ker.x;
            bev.Oleg.mbedata.y = ev.pos.ker.y;
            bev.Oleg.mbedata.button = ev.leftButton ? booba::MouseButton::Left : booba::MouseButton::Right;
        } else if (ev.type == Event::MouseMove) {
            bev.type = booba::EventType::MouseMoved;
            bev.Oleg.motion.x = ev.pos.ker.x;
            bev.Oleg.motion.y = ev.pos.ker.y;
            bev.Oleg.motion.rel_x = ev.prev.ker.x;
            bev.Oleg.motion.rel_y = ev.prev.ker.y;
        } else {
            assert(!"Event is not supported!");
        }
        assert(parent->getCanvas());
        tool->apply(dynamic_cast<booba::Image*>(parent->getCanvas()), &bev);
    }

    void ToolPalette::setupToolBHandler(Event ev)
    {
        assert(ev.type == Event::MousePress);
        booba::Event bev = {};
        bev.type = booba::EventType::ButtonClicked;
        bev.Oleg.bcedata.id = ev.widgetID;
        tools[ev.widgetID]->apply(dynamic_cast<booba::Image*>(parent->getCanvas()), &bev);
    }

    void ToolPalette::setupToolSHandler(Event ev)
    {
        assert(ev.type == Event::MousePress);
        booba::Event bev = {};
        bev.type = booba::EventType::ScrollbarMoved;
        bev.Oleg.smedata.id = ev.widgetID;
        bev.Oleg.smedata.value = ev.curSlider;
        tools[ev.widgetID]->apply(dynamic_cast<booba::Image*>(parent->getCanvas()), &bev);
    }

    void ToolPalette::setupToolCHandler(Event ev)
    {
        booba::Event bev = {};
        if (ev.type == Event::MousePress)
            bev.type = booba::EventType::CanvasMPressed;
        else if (ev.type == Event::MouseRelease)
            bev.type = booba::EventType::CanvasMReleased;
        else if (ev.type == Event::MouseMove)
            bev.type = booba::EventType::CanvasMMoved;
        else
            assert(!"Unknown event!");
        bev.Oleg.smedata.id = ev.widgetID;
        bev.Oleg.cedata.x = ev.pos.ker.x;
        bev.Oleg.cedata.y = ev.pos.ker.y;
        tools[ev.widgetID]->apply(dynamic_cast<booba::Image*>(parent->getCanvas()), &bev);
    }
    void ToolPalette::setToolSetupPos(size_t x, size_t y, size_t w, size_t h)
    {
        ts_x = x;
        ts_y = y;
        ts_w = w;
        ts_h = h;
    }

    void ToolPalette::regButton(uint64_t widgetID)
    {
        tools[widgetID] = curTool;
    }

    void ToolPalette::addTool(booba::Tool *tool)
    {
        assert(tool && "nullptr provided to addTool");
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
        tools[(uint64_t)b] = tool;
        tools[(uint64_t)ts] = tool;
        parent->setToolSetup(ts);
        tool->buildSetupWidget();
    }
}

