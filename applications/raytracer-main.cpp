#include "raytracer-app.hpp"

int main()
{
    raytracer s;
    while (s.isAlive()) {
        s.update();
    }
}
