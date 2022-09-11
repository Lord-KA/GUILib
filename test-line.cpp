#include <iostream>

#include "sdlPlain.hpp"
#include "line.hpp"

int main()
{
    g::sdlPlain p(400, 600, g::color::green);
    g::line l(10, 20, 10, 200, 1001);
    l.draw2plane(p, g::color::red);
    p.render();
}
