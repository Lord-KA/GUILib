#include <iostream>
#include "color.hpp"

int main()
{
    g::color c1 = g::color::red;
    std::cout << (c1 == g::color::red) << std::endl;
}
