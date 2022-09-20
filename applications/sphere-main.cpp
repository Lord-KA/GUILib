#include "sphere-app.hpp"

int main()
{
    sphere s;
    while (s.isAlive()) {
        s.update();
    }
}
