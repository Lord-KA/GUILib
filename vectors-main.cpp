#include "app.hpp"

int main()
{
    app a;
    while (a.isAlive())
        a.run();
}
