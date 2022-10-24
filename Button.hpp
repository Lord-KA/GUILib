#pragma once

#include "Widget.hpp"

namespace gGUI {

    class Button : public Widget
    {
    public:
        Button(size_t x, size_t y, size_t w, size_t h, Widget *p) : Widget(x, y, w, h, p, TextureManager::code::button) {}

        /*
        void draw(sf::RenderWindow &window, size_t p_x, size_t p_y) override
        {
        }
        */
    };
}
