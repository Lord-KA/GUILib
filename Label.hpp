#include "Widget.hpp"

namespace gGUI {

    class Label : public Widget {
    private:
        const char *str;
        sf::Font font;
        sf::Text text;
    public:
        Label(size_t in_x, size_t in_y, size_t in_w, size_t in_h, Widget *p, const char *s)
            : Widget(in_x, in_y, in_w, in_h, p, "badtexture"), str(s)
        {
            assert(font.loadFromFile("../fonts/arial.ttf"));
            text.setFont(font);
            text.setString(str);
            text.setCharacterSize(h);
            resize(-1, -1);
#if 0
            text.setScale(w / text.getLocalBounds().width,
                          h / text.getLocalBounds().height);
#endif
        }

        void draw(sf::RenderWindow &window, size_t p_x, size_t p_y) override
        {
            text.setPosition(x + p_x, y + p_y);
            window.draw(text);
        }

        Widget *belongs(size_t, size_t, size_t x = 0, size_t y = 0) const override
        {
            return nullptr;
        }

        virtual void move(size_t new_x, size_t new_y) override
        {
            Widget::move(new_x, new_y);
            resize(-1, -1);
        }
        virtual void resize(size_t new_w, size_t new_h) override
        {
            Widget::resize(new_w, new_h);
            x = 0.1 * w;
            y = 0.1 * h;
            h = 0.3 * h;
            w = 0.3 * w;
            text.setCharacterSize(h);
        }
    };
}
