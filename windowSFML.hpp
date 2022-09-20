#pragma once

#include "window.hpp"
#include "color.hpp"

#include <SFML/Graphics.hpp>
#include <cassert>

namespace g {
    class windowSFML : public windowAbstr {
    private:
        sf::RenderWindow *window = NULL;
        sf::Font font;

    public:
        windowSFML(int w, int h, char name[])
        {
            width = w;
            height = h;
            window = new sf::RenderWindow(sf::VideoMode(width, height), name);
            assert(window);
            font.loadFromFile("../fonts/arial.ttf");
            window->setActive();
            window->clear();
            window->display();
        }

        ~windowSFML()
        {
            assert(window);
            delete window;
            window = NULL;
        }

        sf::Color convertColor(g::color c)
        {
            return sf::Color(c.getR(), c.getG(), c.getB());
        }

        void drawLine(float x1, float y1, float x2, float y2, g::color c) override
        {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(x1, y1), convertColor(c)),
                sf::Vertex(sf::Vector2f(x2, y2), convertColor(c)),
            };

            window->draw(line, 2, sf::Lines);
        }

        void drawLine(const g::line &l, g::color c) override
        {
            drawLine(l.getKer().x1, l.getKer().y1, l.getKer().x2, l.getKer().y2, c);
        }

        void drawVector(int x0, int y0, const vector &v, color col)
        {
            assert(y0 < height && x0 < width);
            line l(x0, y0, v);
            drawLine(l, col);
            vector ort(-v.getKer().y, v.getKer().x);
            vector arr1 = ( ort - v * 1.6) * 0.1;
            vector arr2 = (-ort - v * 1.6) * 0.1;
            drawLine(line(l.getKer().x2, l.getKer().y2, arr1, 2), col);
            drawLine(line(l.getKer().x2, l.getKer().y2, arr2, 2), col);
        }

        void setBackground(g::color c) override
        {
            window->clear(convertColor(c));
        }

        void update() override
        {
            window->display();
        }

        g::event getEvent() {
            sf::Event e;
            if (!(window->pollEvent(e)))
                return g::event(g::event::None);

            sf::Vector2i pos = sf::Mouse::getPosition();
            pos -= window->getPosition();

            if (e.type == sf::Event::MouseButtonPressed)
                return g::event(g::event::MousePress,   g::vector(pos.x, pos.y));
            else if (e.type == sf::Event::MouseButtonReleased)
                return g::event(g::event::MouseRelease, g::vector(pos.x, pos.y));

            return g::event(g::event::Unsupported);
        }

        void drawText(float x, float y, const std::string &t) override
        {
            sf::Text text;
            text.setFont(font);
            text.setString(t);
            text.setCharacterSize(24);
            text.setFillColor(sf::Color(0, 0, 0));
            text.setPosition(x, y);
            window->draw(text);
        }

    };
}
