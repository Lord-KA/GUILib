#include "MainWindow.hpp"
#include "Button.hpp"

int main()
{
    gGUI::MainWindow w(800, 600, "Hello World");

    gGUI::Button b(10, 10, 100, 100, &w, "Hello");
    gGUI::Button b2(90, 90, 100, 100, &w, "World");

    std::cerr << (w.belongs(30, 30) ? "YES" : "NO") << std::endl;
    w.run();
}
