
#include <iostream>

#include "Collision.hpp"
#include "Entity.hpp"

void COLLISION_MANAGER::registerCollision(ENTITY *ref, const Engine::Entities::Collision &collision) {
    this->collisions[ref].push_back(collision);
}

void COLLISION_MANAGER::checkCollision(ENTITY *entity) {
    auto &collisionBoxes = this->collisions[entity];
    for (auto &oEntity: this->collisions) {
        if (oEntity.first == entity) continue;
        for (auto &oCollision: oEntity.second) {
            for (auto &collision: collisionBoxes) {
                sf::Rect<float> oBox{{oCollision.origin + oEntity.first->position}, {oCollision.size.width, oCollision.size.height}};
                sf::Rect<float> box{{collision.origin + entity->position}, {collision.size.width, collision.size.height}};
                if (oBox.intersects(box)) {
                    oCollision.callback(entity);
                    collision.callback(oEntity.first);
                }
            }
        }
    }
}
