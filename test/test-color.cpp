#include <iostream>
#include "color.hpp"

int main()
{
    g::color c[3] = {g::color::red, g::color::green, g::color::blue};
    std::cout << sizeof c << std::endl;
}
