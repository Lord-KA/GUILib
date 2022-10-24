#pragma once

#include "color.hpp"
#include "line.hpp"
#include "event.hpp"
#include "Widget.hpp"

#include <SFML/Graphics.hpp>
#include <cassert>

namespace gGUI {
    class MainWindow : public Widget
    {
    private:
        sf::RenderWindow *window = NULL;
        sf::Font font;
        bool is_closed;

        void drawLine(float x1, float y1, float x2, float y2, g::color c)
        {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(x1, y1), convertColor(c)),
                sf::Vertex(sf::Vector2f(x2, y2), convertColor(c)),
            };

            window->draw(line, 2, sf::Lines);
        }

        void drawLine(const g::line &l, g::color c)
        {
            drawLine(l.getKer().x1, l.getKer().y1, l.getKer().x2, l.getKer().y2, c);
        }

        void drawText(float x, float y, const std::string &t)
        {
            sf::Text text;
            text.setFont(font);
            text.setString(t);
            text.setCharacterSize(24);
            text.setFillColor(sf::Color(0, 0, 0));
            text.setPosition(x, y);
            window->draw(text);
        }

        void setBackground(g::color c)
        {
            window->clear(convertColor(c));
        }

        sf::Color convertColor(g::color c)
        {
            return sf::Color(c.getR(), c.getG(), c.getB());
        }

        void update()
        {
            window->display();
        }

        g::event getEvent()
        {
            sf::Event e;
            if (!(window->pollEvent(e)))
                return g::event(g::event::None);

            sf::Vector2i pos = sf::Mouse::getPosition();
            pos -= window->getPosition();

            if (e.type == sf::Event::MouseButtonPressed)
                return g::event(g::event::MousePress,   g::vector2f(pos.x, pos.y));
            else if (e.type == sf::Event::MouseButtonReleased)
                return g::event(g::event::MouseRelease, g::vector2f(pos.x, pos.y));

            return g::event(g::event::Unsupported);
        }

    public:
        MainWindow(int w, int h, char name[]) : Widget(0, 0, w, h, nullptr)
        {
            window = new sf::RenderWindow(sf::VideoMode(w, h), name);
            assert(window);
            assert(font.loadFromFile("../fonts/arial.ttf"));
            window->setActive();
            window->clear();
            window->display();
            manager = new TextureManager;
            assert(manager);
        }

        ~MainWindow()
        {
            assert(window);
            delete window;
            window = nullptr;
            delete manager;
            manager = nullptr;
        }

        void run()
        {
            while (not is_closed) {
                draw(*window, 0, 0);
            }
        }

        void draw(sf::RenderWindow &w, size_t, size_t) override
        {
            setBackground(g::color::gray);
            for (auto child : children) {
                child->draw(w, 0, 0);
            }
            update();
        }
    };
}
