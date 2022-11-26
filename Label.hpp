#include "Widget.hpp"

namespace gGUI {

    class Label : public Widget {
    private:
        const char *str;
        sf::Font font;
        sf::Text text;
    public:
        Label(size_t x, size_t y, size_t w, size_t h, Widget *p, char *s) : Widget(x, y, w, h, p, "badtexture"), str(s)
        {
            assert(font.loadFromFile("../fonts/arial.ttf"));
            text.setFont(font);
            text.setString(str);
            text.setCharacterSize(h);
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
    };
}
