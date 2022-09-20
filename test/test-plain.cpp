#include "sdlPlain.hpp"

int main() {
    g::sdlPlain p(5, 10);
    p(4, 9) = g::color(g::color::red);
}
