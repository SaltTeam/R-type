//
// Created by delacr_a on 17/01/18.
//

#pragma once

#include "entities/powerups/APowerUp.hpp"

namespace Entities {
    class HealPowerUp : public APowerUp {
    public:
        HealPowerUp(SCOPE *scope, uint64_t id, GRADE grade, int x, int y)
                : APowerUp(scope, id, isEnabled, x, y, 0, 0.1, grade) {
            switch (grade) {
                case BRONZE:
                    this->setTexture("resources/sprites/Power-ups/star_bronze.png");
                    break;
                case SILVER:
                    this->setTexture("resources/sprites/Power-ups/star_silver.png");
                    break;
                case GOLD:
                    this->setTexture("resources/sprites/Power-ups/star_gold.png");
                    break;
            }
            this->position.x -= this->texture->sprite.getGlobalBounds().width / 2;
            std::function<void(ENTITY *)> f = std::bind(&APowerUp::onCollision, this, std::placeholders::_1);
            this->registerCollisionBox(this->texture->sprite.getGlobalBounds(), f);
        };

        void interract(Entities::PlayerShip *ship) override {
            ship->gainHealth(grade);
        }
    };
}