#include <iostream>

#include "sdlPlain.hpp"
#include "line.hpp"


void drawGrid(int x, int y, int h, int w, int d, g::sdlPlain &p, g::color color)
{
    for (int i = 0; i <= h; ++i)
        p.draw(g::line(x + i * d,
                       y,
                       x + i * d,
                       y + w * d, 1), color);

    for (int j = 0; j <= w; ++j)
        p.draw(g::line(x,
                       y + j * d,
                       x + h * d,
                       y + j * d, 1), color);
}

int main()
{
    g::sdlPlain p(600, 600, g::color::white);
    g::vector v(40, -100);
    drawGrid(20, 20, 27, 27, 20, p, g::color::gray);
    p.draw(300, 300, v, g::color::red);
    // p.draw(g::line(150, 130, 50, 30, 3), g::color::green);
    p.render();
}
