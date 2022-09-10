#include "plain.hpp"

int main() {
    g::plain p(5, 10);
    p(4, 9) = g::color(g::color::red);
}
