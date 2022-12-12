#pragma once

#include "tools.hpp"

namespace booba {

    static const int RED = 0xff0000ff;

    class MyTool1 : public Tool {
    public:
        virtual void apply(Image *img, const Event *ev) override
        {
            std::cerr << "DEBUG: Called Apply!\n";
            for (size_t i = 0; i < 100; ++i)
                for (size_t j = 0; j < 100; ++j)
                    img->setPixel(i + 200, j + 40, RED);
        }

        virtual const char *getTexture() override
        {
            return "../textures/button.png";
        }

        virtual void buildSetupWidget() override
        {
            createButton(0, 0, 100, 100, "MyButton");
        }

        virtual ~MyTool1() override {}
    };

    class MyTool2 : public Tool {
    public:
        virtual void apply(Image *img, const Event *ev) override
        {
            std::cerr << "DEBUG: Called Apply!\n";
            for (size_t i = 0; i < 100; ++i)
                for (size_t j = 0; j < 100; ++j)
                    img->setPixel(i + 40, j + 200, RED);
        }

        virtual const char *getTexture() override
        {
            return "../textures/button.png";
        }

        virtual void buildSetupWidget() override
        {
            createButton(100, 0, 100, 100, "Another");
        }
    };

    class DrawTool : public Tool {
    private:
        bool active = false;
    public:
        virtual void apply(Image *img, const Event *ev) override
        {
            if (ev->type == EventType::MousePressed) {
                std::cerr << "MousePressed!\n";
                if (!active)
                    return;
                size_t x = ev->Oleg.mbedata.x;
                size_t y = ev->Oleg.mbedata.y;
                for (size_t i = 0; i < 20; ++i)
                    for (size_t j = 0; j < 20; ++j) {
                        img->setPixel(x + i, y + j, RED);
                    }
            } else if (ev->type == EventType::ButtonClicked) {
                active ^= 1;
            }
        }

        virtual const char *getTexture() override
        {
            return "../textures/button.png";
        }

        virtual void buildSetupWidget() override
        {
            createButton(0, 100, 100, 100, "Draw");
        }
    };
}
