//
// Created by delacr_a on 17/01/18.
//

#pragma once

#include "entities/powerups/APowerUp.hpp"

namespace Entities {
    class ShieldPowerUp : public APowerUp {
    public:
        ShieldPowerUp(SCOPE *scope, uint64_t id, GRADE grade, int x, int y)
                : APowerUp(scope, id, true, x, y, 0, 0.1, grade) {
            this->registerTexture("resources/sprites/Power-ups/shield_" + this->getEnumName(grade) + ".png");
        };

        void interract(PlayerShip *ship) override {
            ship->gainShield(grade);
        }
    };
}