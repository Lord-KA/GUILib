#include "windowSFML.hpp"
#include "button.hpp"

static const g::vector2f leftDefault(120, -100);
static const g::vector2f rightDefault(50, 50);

class app {
private:
    g::windowAbstr *window = NULL;
    g::vector2f left;
    g::vector2f right;
    g::button exitButton;
    g::button resetButton;
    bool alive = true;

public:
    app()
    {
        window = new g::windowSFML(600, 400, "myApp");
        assert(window);
        window->setBackground(g::color::blue);
        left = leftDefault;
        right = rightDefault;
        exitButton = g::button(window, 360, 250, 40, 65, "Exit");
        resetButton = g::button(window, 460, 250, 40, 85, "Reset");
    }
    ~app()
    {
        assert(window);
        delete window;
    }

    void reset()
    {
        left = leftDefault;
        right = rightDefault;
    }

    void exit()
    {
        alive = false;
    }

    bool isAlive()
    {
        return alive;
    }

    void processEvents()
    {
        g::event ev = window->getEvent();
        while (ev.type != g::event::None) {
            if (exitButton.handleEvent(ev)) {
                exit();
            } else if (resetButton.handleEvent(ev)) {
                reset();
            } else {
                int x = ev.pos.getKer().x;
                int y = ev.pos.getKer().y;
                if (ev.type == g::event::MousePress) {
                    if (10 < x && x < 20 * 16 + 10 && 10 < y && y < 20 * 16 + 10) {   // inside left grid
                        std::cerr << "MouseButtonPressed at (" << x << ", " << y << ")\n";

                        left = ev.pos - g::vector2f(160, 160);
                    }
                }
            }

            ev = window->getEvent();
        }
    }

    void run()
    {
        assert(window);
        processEvents();

        window->setBackground(g::color::white);

        drawGrid(20,  20, 15, 15, 20, g::color::gray);      // left

        drawGrid(400, 20, 8,  8,  20, g::color::gray);      // right

        right = right.rotate(0.1);
        #ifdef EXTRA_VERBOSE
            std::cout << right << std::endl;
        #endif

        window->drawVector(160, 160, left, g::color::red);

        window->drawVector(480, 100, right, g::color::blue);

        exitButton.draw();
        resetButton.draw();

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

    void drawButton(float x, float y, float w, float h, const std::string &text)
    {
        window->drawLine(x, y, x, y + h, g::color::gray);
        window->drawLine(x + w, y, x + w, y + h, g::color::gray);
        window->drawLine(x, y, x + w, y, g::color::gray);
        window->drawLine(x, y + h, x + w, y + h, g::color::gray);

        window->drawText(x + 10, y + h / 2 - 14, text);
    }
};
