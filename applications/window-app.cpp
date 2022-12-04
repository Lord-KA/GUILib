#include "MainWindow.hpp"
#include "Button.hpp"
#include "Slider.hpp"
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

    gGUI::DropOutMenu dom(0, 0, 100, 100, &tb, "Menu");
    gGUI::Button b3(90, 90, 100, 30, &dom, "Foo");
    gGUI::Button b4(10, 10, 100, 30, &dom, "Bar");

    gGUI::ToolPalette tp(0, 200, 6, 4, 40, &w);
    gGUI::Canvas c(600, 200, 1100, 700, &w);

    tp.setToolSetupPos(0, 400, 500, 400);

    // gGUI::Slider sldr(300, 300, 200, 50, &w, 0, 10, 0);

    w.initPlugins("../Plugins");

    booba::ApplicationContext ac;
    ac.fgColor = 0xff0000ff;
    booba::APPCONTEXT = &ac;

    /*
    booba::MyTool1 tool1;
    booba::MyTool2 tool2;
    booba::DrawTool tool3;
    booba::addTool(&tool1);
    booba::addTool(&tool2);
    booba::addTool(&tool3);
    */

    w.run();
}
