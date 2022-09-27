#include "ray.hpp"

int main()
{
    g::material m;
    g::sphere s({0, 0, 0}, 10, m);
    g::ray r({0, 5, 0}, {0, 5, 0}, m);
    std::cout << r.traverse(s) << std::endl;
}
