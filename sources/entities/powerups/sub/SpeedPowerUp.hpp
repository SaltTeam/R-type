//
// Created by delacr_a on 17/01/18.
//

#pragma once

#include "entities/powerups/APowerUp.hpp"

namespace Entities {
    class SpeedPowerUp : public APowerUp {
    public:
        SpeedPowerUp(SCOPE *scope, uint64_t id, network::protocol::PlayerColor playerColor, GRADE grade, int x, int y)
                : APowerUp(scope, id, playerColor, true, x, y, 0, 0.1, grade) {
            this->registerTexture("resources/sprites/Power-ups/bolt_" + this->getEnumName(grade) + ".png");
        };

        void interract(PlayerShip *ship) override {
            ship->gainSpeed(grade);
        }
    };
}