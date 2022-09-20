#include "window.hpp"

namespace g {
    class button {
    private:
        g::windowAbstr *window = NULL;
        int x;
        int y;
        int h;
        int w;
        std::string text;

    public:
        button() : window(NULL), x(-1), y(-1), h(-1), w(-1) {}
        button(g::windowAbstr *window, int x, int y, int h, int w, const std::string &t) : window(window), x(x), y(y), h(h), w(w), text(t) {}

        void draw()
        {
            assert(window);
            window->drawLine(x, y, x, y + h, g::color::gray);
            window->drawLine(x + w, y, x + w, y + h, g::color::gray);
            window->drawLine(x, y, x + w, y, g::color::gray);
            window->drawLine(x, y + h, x + w, y + h, g::color::gray);

            window->drawText(x + 10, y + h / 2 - 14, text);
        }

        bool handleEvent(g::event ev)
        {
            if (ev.type == g::event::MousePress) {
                int mcX = ev.pos.getKer().x;
                int mcY = ev.pos.getKer().y;
                if (mcX >= x && mcY >= y && mcX <= x + w && mcY <= y + h) {
                    return true;
                }
            }
            return false;
        }
    };
}
