#pragma once

#include "Widget.hpp"
#include "ToolSetup.hpp"

#include "tools.hpp"

namespace gGUI {

    class ToolPalette : public Widget {
    private:
        size_t w_cnt = 0;
        size_t h_cnt = 0;
        size_t d = 0;

        std::vector<Widget*> tools;

        Widget *&curToolSetup;//TODO

    public:
        Slot CanvasMouseAct;
        //TODO think of a way to connect tool buttons via slots

        ToolPalette(size_t x, size_t y, size_t w_cnt, size_t h_cnt, size_t d, MainWindow *p)
            : Widget(x, y, w_cnt * d, h_cnt * d, p, "graypanel"),
              w_cnt(w_cnt), h_cnt(h_cnt), d(d), curToolSetup(p->getToolSetup())
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

        void addTool(booba::Tool *tool)
        {
            Button b = new Button(this, tool->getTexture());
            //TODO connect button signal
            curToolSetup->hide();
            // curToolSetup = new ToolSetup() //TODO add args
            curToolSetup->hide();
            tools.push_back(curToolSetup);
            tool->buildSetupWidget();
        }
    };
}
