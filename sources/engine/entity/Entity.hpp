
#pragma once

#include <cstdint>
#include <map>
#include <SFML/System/Vector2.hpp>

#include "engine/ForwardDeclaration.hpp"
#include "engine/display/Texture.hpp"

namespace Engine {
    namespace Entities {

        class BaseEntity {
            friend ENTITY_MANAGER;

        public:
            uint64_t id;
            bool isEnabled;
            sf::Vector2<double> position;
            std::unique_ptr<TEXTURE> texture;

            explicit BaseEntity(uint64_t id, const std::string &texturePath, bool isEnabled = true)
                    : id(id), isEnabled(isEnabled) {}

            virtual ~BaseEntity() = default;

            void setTexture(std::unique_ptr<TEXTURE> &texture) {
                this->texture = std::move(texture);
            }

        protected:
            virtual void update() = 0;
        };

        enum class Layer : unsigned int {
            NotDisplayed = 0,
            Layer1,
            Layer2,
            Layer3,
            Layer4,
            Layer5
        };

        class EntityManager {
        private:
            std::map<Layer, ENTITY *> entities;

        public:

        };

    }
}
