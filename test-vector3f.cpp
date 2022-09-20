#include "vector3f.hpp"

int main()
{
    g::vector3f v1 = {3, 3, 3};
    std::cout << v1.normalize() << std::endl;
}
