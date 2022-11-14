#pragma once

#include <SFML/Graphics.hpp>
#include <cassert>

namespace gGUI {
    class TextureManager {
    public:
        sf::Image   *images;
        sf::Texture *textures;

        enum code {
            button,
            badtexture,
            cnt,
        };

        TextureManager()
        {
            textures = new sf::Texture[cnt];
            images   = new sf::Image[cnt];
            assert(textures && images);
            for (size_t i = 0; i < cnt; ++i) {
                assert(images[i].loadFromFile(filenames[i]));
                textures[i].loadFromImage(images[i]);
            }
        }

        ~TextureManager()
        {
            assert(textures && images);
            delete[] textures;
            delete[] images;
        }

        const sf::Texture& operator[](size_t pos) const
        {
            assert(textures);
            assert(pos < cnt);
            return textures[pos];
        }

    private:
        char filenames[cnt][100] = {
            [button]     = "../textures/button.png",
            [badtexture] = "../textures/badtexture.png",
        };
    };
}
