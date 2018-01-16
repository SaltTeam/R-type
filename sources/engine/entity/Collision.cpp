
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
                sf::Rect<float> oBox{{oCollision.origin + oEntity.first->position}, {oCollision.size + oEntity.first->position}};
                sf::Rect<float> box{{collision.origin + entity->position}, {collision.size + entity->position}};
                if (oBox.intersects(box)) {
                    oCollision.callback(oEntity.first);
                    collision.callback(entity);
                }
            }
        }
    }
}
