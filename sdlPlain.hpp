#pragma once

#include <stdlib.h>
#include <SDL2/SDL.h>

#include "plain.hpp"
#include "color.hpp"

static const size_t channels = sizeof(g::color);

namespace g {
    class sdlPlain : public plain {
    private:
        // XXX SDL_Event event;
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
            SDL_CreateWindowAndRenderer(height, width, 0, &window, &renderer);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            SDL_RenderClear(renderer);
        }

        void sdlTeardown()
        {
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
        }

        void render() override
        {
        #if 0
            size_t rmask = 0xff0000;
            size_t gmask = 0x00ff00;
            size_t bmask = 0x0000ff;
            size_t amask = 0x000000;
        #else
            size_t rmask = 0x000000ff;
            size_t gmask = 0x0000ff00;
            size_t bmask = 0x00ff0000;
            size_t amask = 0xff000000;
        #endif

            SDL_Surface *surface = SDL_CreateRGBSurfaceFrom((void*)window,
                width,
                height,
                channels * 8,      // bits per pixel = 24
                width * channels,  // pitch
                rmask, gmask, bmask, 0);

            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderPresent(renderer);
            SDL_Delay(5000);
            SDL_FreeSurface(surface);
        }
    };
}
