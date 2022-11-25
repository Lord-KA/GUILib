#include "MainWindow.hpp"
#include "Button.hpp"
#include "TopBar.hpp"
#include "DropOutMenu.hpp"

int main()
{
    gGUI::MainWindow w(800, 600, "Hello World");

    gGUI::TopBar tb(&w);
    gGUI::Button b1(10, 10, 100, 100, &tb, "Hello");
    gGUI::Button b2(90, 90, 100, 100, &tb, "World");

    gGUI::DropOutMenu dom(0, 0, 120, 120, &tb, "Menu");
    gGUI::Button b3(90, 90, 100, 100, &dom, "Foo");
    gGUI::Button b4(10, 10, 100, 100, &dom, "Bar");

    w.run();
}
