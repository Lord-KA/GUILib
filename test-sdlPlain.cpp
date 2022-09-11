#include "sdlPlain.hpp"
#include <iostream>

int main()
{
    g::sdlPlain p(400, 600, g::color::black);
    std::cout << "channels = " << sizeof(g::color) << std::endl;
    std::cout << "color == " << p(23, 300) << std::endl;
    p.render();
}
