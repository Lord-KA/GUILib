#include "MainWindow.hpp"
#include "Button.hpp"
#include "TopBar.hpp"
#include "DropOutMenu.hpp"
#include "Canvas.hpp"
#include "ToolPalette.hpp"
#include "forTools.hpp"

#include "testTool.hpp"

int main()
{
    gGUI::MainWindow w(1920, 1000, "Hello World");
    booba::MAINWINDOW = &w;

    gGUI::TopBar tb(&w, 60);
    gGUI::Button b1(10, 10, 100, 100, &tb, "Hello");
    gGUI::Button b2(90, 90, 100, 100, &tb, "World");

    gGUI::DropOutMenu dom(0, 0, 120, 120, &tb, "Menu");
    gGUI::Button b3(90, 90, 100, 30, &dom, "Foo");
    gGUI::Button b4(10, 10, 100, 30, &dom, "Bar");

    gGUI::ToolPalette tp(0, 200, 6, 4, 40, &w);
    gGUI::Button b5(10, 10, 100, 100, &tp, "One");
    gGUI::Button b6(90, 90, 100, 100, &tp, nullptr, "../textures/buttonbgmouseover.png");
    gGUI::Canvas c(300, 300, 600, 600, &w);

    /*
    gGUI::ToolSetup t(0, 500, 200, 400, &w);
    w.setToolSetup(&t);
    booba::createButton(0, 0, 100, 100, "MyButton");
    */

    tp.setToolSetupPos(0, 500, 200, 400);

    booba::MyTool tool;
    booba::addTool(&tool);

    w.run();
}
