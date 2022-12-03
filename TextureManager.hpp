#pragma once

#include <SFML/Graphics.hpp>
#include <cassert>
#include <string>
#include <iostream>
#include <unordered_map>

namespace gGUI {
    class TextureManager {
    public:
        std::unordered_map<std::string, sf::Texture> textures;
        std::unordered_map<std::string, sf::Image> images;

        TextureManager()
        {
            for (size_t i = 0; i < filenames.size(); ++i) {
                const std::string &file = filenames[i];
                std::string name = file.substr(file.rfind("/") + 1, file.rfind(".png") - file.rfind("/") - 1);
                images[name] = sf::Image();
                if (not images[name].loadFromFile(file)) {
                    std::cerr << "ERROR: no such image (" << name << ")\n";
                    assert(false);
                }
                textures[name] = sf::Texture();
                assert(textures[name].loadFromImage(images[name]));
            }
        }

        const sf::Texture& operator[](const std::string &name)
        {
            return get(name);
        }

        const sf::Texture& get(const std::string &name)
        {
            assert(name != "NONE");
            if (not textures.contains(name)) {
                if (not images[name].loadFromFile(name))
                    images[name] = images["badtexture"];
                textures[name].loadFromImage(images[name]);
            }
            return textures[name];
        }

    private:
        const std::vector<std::string> filenames = {
            "../textures/button.png",
            "../textures/badtexture.png",
            "../textures/buttonbg.png",
            "../textures/panel.png",
            "../textures/graypanel.png",
            "../textures/blue_oval.png",
            "../textures/darkgraypanel.png",
        };
    };
}
