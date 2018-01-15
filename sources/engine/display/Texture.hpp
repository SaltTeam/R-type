
#pragma once

#include <string>
#include <SFML/Graphics.hpp>

namespace Engine {
    namespace Display {
        class Texture {
        public:
            std::string path;

            explicit Texture(const std::string &path) : path(path) {}

            virtual ~Texture() = default;
        };

        class SFMLTexture : public Texture {
        public:
            sf::Sprite sprite;
            sf::Texture texture;

            explicit SFMLTexture(const std::string &path) : Texture(path) {
                texture.loadFromFile(path);
                texture.setSmooth(true);
                sprite.setTexture(texture);
                sprite.setScale(sprite.getScale().x / 2, sprite.getScale().y / 2);
            }

            ~SFMLTexture() override = default;
        };
    }
}
