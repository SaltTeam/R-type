
#pragma once

#include <functional>
#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include <unordered_map>
#include "engine/ForwardDeclaration.hpp"

namespace Engine {
    namespace Entities {
        struct Collision {
            std::function<void(ENTITY *)> callback;
            sf::Vector2f origin; // Will be added to the entity position
            sf::Vector2f size;
        };

        class CollisionManager {
        private:
            std::unordered_map<ENTITY *, std::vector<Collision>> collisions;

        public:
            void registerCollision(ENTITY *ref, const Collision &collision);

            void checkCollision(ENTITY *entity);
        };
    }
}
