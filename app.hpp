#include "windowSFML.hpp"

class app {
private:
    g::windowAbstr *window = NULL;
    g::vector left;
    g::vector right;

public:
    app()
    {
        window = new g::windowSFML(600, 400, "myApp");
        assert(window);
        window->setBackground(g::color::blue);
        left = g::vector(120, -100);
        right = g::vector(40, 40);
    }
    ~app()
    {
        assert(window);
        delete window;
    }

    void run()
    {
        assert(window);
        window->processEvents();

        window->setBackground(g::color::white);

        drawGrid(20, 20, 15, 15, 20, g::color::gray);

        drawGrid(400, 20, 8, 8, 20, g::color::gray);

        right = right.rotate(0.1);
        #ifdef EXTRA_VERBOSE
            std::cout << right << std::endl;
        #endif

        window->drawVector(160, 160, left, g::color::red);

        window->drawVector(480, 100, right, g::color::blue);

        sf::sleep(sf::microseconds(100000)); //TODO set up to ~60 FPS

        window->update();
    }
    void drawGrid(float x, float y, int w, int h, int d, g::color c)
    {
        for (int i = 0; i <= w; ++i)
            window->drawLine(x, y + i * d, x + h * d, y + i * d, c);

        for (int j = 0; j <= h; ++j)
            window->drawLine(x + j * d, y, x + j * d, y + w * d, c);
    }
};
