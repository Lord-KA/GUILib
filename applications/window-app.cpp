#include "MainWindow.hpp"
#include "Button.hpp"
#include "TopBar.hpp"
#include "DropOutMenu.hpp"
#include "Canvas.hpp"
#include "ToolPalette.hpp"
#include "forTools.hpp"

int main()
{
    gGUI::MainWindow w(800, 600, "Hello World");
    booba::MAINWINDOW = &w;

    gGUI::TopBar tb(&w, 60);
    gGUI::Button b1(10, 10, 100, 100, &tb, "Hello");
    gGUI::Button b2(90, 90, 100, 100, &tb, "World");

    gGUI::DropOutMenu dom(0, 0, 120, 120, &tb, "Menu");
    gGUI::Button b3(90, 90, 100, 30, &dom, "Foo");
    gGUI::Button b4(10, 10, 100, 30, &dom, "Bar");

    gGUI::ToolPalette ts(0, 200, 1, 6, 40, &w);
    gGUI::Button b5(10, 10, 100, 100, &ts, "One");
    gGUI::Button b6(90, 90, 100, 100, &ts, nullptr, "../textures/buttonbgmouseover.png");
    gGUI::Canvas c(200, 200, 400, 400, &w);

    w.run();
}
