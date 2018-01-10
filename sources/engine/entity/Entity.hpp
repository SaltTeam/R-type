
#pragma once

#include <cstdint>
#include <SFML/System/Vector2.hpp>

#include "engine/ForwardDeclaration.hpp"

namespace Engine {
    namespace Entities {

        class BaseEntity {
            friend ENTITY_MANAGER;

        public:
            sf::Vector2<double> position;

            uint64_t id;

            bool isEnabled;

            explicit BaseEntity(uint64_t id, bool isEnabled = true) : id(id), isEnabled(isEnabled) {}

            virtual ~BaseEntity() = default;

        protected:
            virtual void update() = 0;
        };

        class EntityManager {
        private:


        public:

        };

    }
}
