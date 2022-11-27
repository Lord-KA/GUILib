#pragma once

#include <vector>
#include <string>
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

        bool isShown = true;

        Widget *parent;
        std::vector<Widget*> children;
        TextureManager *manager;

        sf::Sprite sprite;

        std::string texture;

        void setTexture(std::string t)
        {
            assert(manager != nullptr);
            texture = t;
            sprite.setTexture(manager->get(t));
            sprite.setScale(w / sprite.getLocalBounds().width,
                            h / sprite.getLocalBounds().height);
        }

    public:
        Widget(size_t x, size_t y, size_t w, size_t h, Widget *p = nullptr, std::string t = "badtexture")
                : x(x), y(y), w(w), h(h), parent(p), manager(nullptr), texture(t)
        {
            printf("Widget (%p) created with parent (%p)!\n", this, p);
            if (parent != nullptr) {
                parent->add_child(this);
                manager = parent->manager;
                if (manager != nullptr and texture != "NONE")
                    setTexture(texture);
            }
        }

        virtual void draw(sf::RenderWindow &window, size_t p_x, size_t p_y)
        {
            if (not isShown)
                return;
            sprite.setPosition(p_x + x, p_y + y);
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
            if (not isShown)
                return nullptr;

            for (auto child : children) {
                Widget *res = child->belongs(pos_x, pos_y, parent_x + x, parent_y + y);
                if (res)
                    return res;
            }

            if ((pos_x <= x + parent_x) || (pos_y <= y + parent_y)
                    || (w <= pos_x - x - parent_x) || (h <= pos_y - y - parent_y))
                return nullptr;

            assert(manager);
            if (texture == "NONE")
                return nullptr;

            size_t cur_x = pos_x - parent_x - x;
            size_t cur_y = pos_y - parent_y - y;
            cur_x *= sprite.getLocalBounds().width  / w;
            cur_y *= sprite.getLocalBounds().height / h;
            sf::Color c = manager->images[texture].getPixel(cur_x, cur_y);
            if (c.a == 0)
                return nullptr;
            return (Widget*)this;
        }

        virtual void move(size_t new_x, size_t new_y)
        {
            x = new_x;
            y = new_y;
        }

        virtual void resize(size_t new_w, size_t new_h)
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

        void show()
        {
            isShown = true;
        }

        void hide()
        {
            isShown = false;
        }

        void setParent(Widget *w)
        {
            assert(w != nullptr);
            parent = w;
            manager = w->manager;
            assert(manager);
            setTexture(texture);
            for (auto ch : children)
                ch->setParent(this);
        }

        virtual void emitSignals(Event ev) {}

        virtual void postload()
        {
            for (auto ch : children)
                ch->postload();
        }
    };
}
