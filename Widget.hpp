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

        void setTexture(TextureManager::code c)
        {
            assert(manager != nullptr);
            sprite.setTexture((*manager)[code]);
            sprite.setScale(w / sprite.getLocalBounds().width,
                            h / sprite.getLocalBounds().height);
        }

    public:
        Widget(size_t x, size_t y, size_t w, size_t h, Widget *p = nullptr, TextureManager::code c = TextureManager::code::badtexture)
                : x(x), y(y), w(w), h(h), parent(p), manager(nullptr), code(c)
        {
            printf("Widget (%p) created!\n", this);
            if (parent != nullptr) {
                parent->add_child(this);
                manager = parent->manager;
                assert(manager != nullptr);
                if (code != TextureManager::code::cnt)
                    setTexture(c);
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
                    || (w <= pos_x - x - parent_x) || (h <= pos_y - y - parent_y))
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

        void move(size_t new_x, size_t new_y)
        {
            x = new_x;
            y = new_y;
        }

        void resize(size_t new_w, size_t new_h)
        {
            if (new_w != -1)
                w = new_w;
            if (new_h != -1)
                h = new_h;
        }

        size_t getWidth() const
        {
            return w;
        }

        size_t getHeight() const
        {
            return h;
        }

        size_t getX() const
        {
            return x;
        }

        size_t getY() const
        {
            return y;
        }

        void setParent(Widget *w)
        {
            assert(w != nullptr);
            parent = w;
            manager = w->manager;
            assert(manager);
            setTexture(code);
        }

        virtual void emitSignals(Event ev) {}
    };
}
