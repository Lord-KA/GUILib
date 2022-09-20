#include "windowSFML.hpp"
#include <iostream>

int main()
{
    g::windowSFML w(600, 400, "myWindow");

    w.drawLine(10.f, 10.f, 200.f, 100.f, g::color::red);

    while (true) {
        w.update();
    }
}
