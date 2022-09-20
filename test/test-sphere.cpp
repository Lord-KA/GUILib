#include "sphere.hpp"

int main()
{
    sphere s;
    while (s.isAlive()) {
        s.update();
    }
}
