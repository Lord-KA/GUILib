#pragma once

#include "tools.hpp"

namespace booba {
    class MyTool : public Tool {
    public:
        virtual void apply(Image *img, const Event *ev) override
        {
            std::cerr << "DEBUG: Called Apply!\n";
            for (size_t i = 0; i < 10; ++i)
                for (size_t j = 0; j < 10; ++j)
                    img->putPixel(i + 100, j + 100, 0xffffffff);
        }

        virtual const char *getTexture() override
        {
            return "../textures/button.png";
        }

        virtual void buildSetupWidget() override
        {
            createButton(0, 0, 100, 100, "MyButton");
        }

        virtual ~MyTool() override {}
    };

    Tool::~Tool() {};
}
