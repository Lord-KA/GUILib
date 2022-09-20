#pragma once

#include <stdlib.h>
#include <SDL2/SDL.h>

#include "plain.hpp"
#include "color.hpp"

static const size_t channels = sizeof(g::color);

namespace g {
    class sdlPlain : public plain {
    private:
        SDL_Renderer *renderer;
        SDL_Window *window;

    public:
        sdlPlain(size_t w, size_t h, color c = color::black) : plain(w, h, c)
        {
            sdlSetup();
        }
        ~sdlPlain()
        {
            sdlTeardown();
        }

        void sdlSetup()
        {
            SDL_Init(SDL_INIT_VIDEO);
            SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
        }

        void sdlTeardown()
        {
            SDL_Delay(2000);    // FIXME
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
        }

        void render() override
        {
            SDL_Surface *surface = SDL_CreateRGBSurfaceFrom((void*)pixels,
                width,
                height,
                channels * 8,       // bits per pixel = 24
                width * channels,   // pitch
                0x000000ff,         // red mask
                0x0000ff00,         // green mask
                0x00ff0000,         // blue mask
                0xff000000);        // alpha mask

            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);
        }
    };
}
