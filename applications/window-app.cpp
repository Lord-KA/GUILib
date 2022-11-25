#include "MainWindow.hpp"
#include "Button.hpp"
#include "TopBar.hpp"

int main()
{
    gGUI::MainWindow w(800, 600, "Hello World");

    gGUI::TopBar tb(&w);
    gGUI::Button b2(90, 90, 100, 100, &tb, "World");
    gGUI::Button b1(10, 10, 100, 100, &tb, "Hello");

    w.run();
}
