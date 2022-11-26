#pragma once

#include "Widget.hpp"

#include "tool.hpp"

namespace gGUI {
    class Tool : public Widget, public booba::Tool {
    public:
        virtual void apply(booba::Image *image, const booba::Event *event)
        {

        }
    };
}
