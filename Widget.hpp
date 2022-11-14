#pragma once

#include <list>
#include <cassert>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Events.hpp"
#include "TextureManager.hpp"

using size_t = long unsigned;

namespace gGUI {

    class Widget
    {
    protected:
        size_t x;
        size_t y;
        size_t w;
        size_t h;

        Widget *parent;
        std::list<Widget*> children;
        TextureManager *manager;

        sf::Sprite sprite;

        TextureManager::code code;

    public:
        Widget(size_t x, size_t y, size_t w, size_t h, Widget *p = nullptr, TextureManager::code c = TextureManager::code::badtexture)
                : x(x), y(y), w(w), h(h), parent(p), manager(nullptr), code(c)
        {
            std::cerr << "Widget created!\n";
            if (parent != nullptr) {
                parent->add_child(this);
                manager = parent->manager;
            }

            if (code != TextureManager::code::cnt) {
                assert(manager != nullptr);
                sprite.setTexture((*manager)[code]);
                sprite.setScale(w / sprite.getLocalBounds().width,
                                h / sprite.getLocalBounds().height);
            }
        }

        virtual void draw(sf::RenderWindow &window, size_t p_x, size_t p_y)
        {
            sprite.setPosition(p_x + x, p_y + y);
            sprite.setColor(sf::Color::Red);
            window.draw(sprite);
            for (auto child : children)
                child->draw(window, p_x + x, p_y + y);
        }

        virtual void add_child(Widget *child)
        {
            assert(child != nullptr);
            children.push_back(child);
        }

        virtual Widget* belongs(size_t pos_x, size_t pos_y, size_t parent_x = 0, size_t parent_y = 0) const
        {
            if ((pos_x <= x + parent_x) || (pos_y <= y + parent_y)
                    || (h <= pos_x - x - parent_x) || (w <= pos_y - y - parent_y))
                return nullptr;

            Widget *res = nullptr;
            for (auto child : children) {
                res = child->belongs(pos_x, pos_y, parent_x + x, parent_y + y);
                if (res)
                    return res;
            }
            assert(manager);
            if (code >= TextureManager::code::cnt)
                return nullptr;

            size_t cur_x = pos_x - parent_x - x;
            size_t cur_y = pos_y - parent_y - y;
            cur_x *= sprite.getLocalBounds().width  / w;
            cur_y *= sprite.getLocalBounds().height / h;
            sf::Color c = manager->images[code].getPixel(cur_x, cur_y);
            if (c.a == 0)
                return nullptr;
            return (Widget*)this;
        }

        virtual void emitSignals(Event ev) {}
    };
}
