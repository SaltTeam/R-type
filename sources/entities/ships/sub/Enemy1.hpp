//
// Created by delacr_a on 17/01/18.
//

#pragma once

#include <entities/weapons/sub/Laser1.hpp>
#include "entities/ships/Ship.hpp"

namespace Entities {
    class Enemy1 : public Ship {
    public:
        Enemy1(SCOPE *scope, uint64_t id = 0, bool isEnabled = true, const float &x = 0, const float &y = 0)
                : Ship(scope, id, "resources/sprites/ships/enemy/ship1/base.png", isEnabled, Entities::Ship::GAME, x,
                       y, 0.25, 0.25, 10) {
            this->weapon = new Entities::Laser1(scope, id);
            this->weapon->setYSpeed(-(this->weapon->getYSpeed()));
            this->canons.push_back({14, 10});
            this->canons.push_back({28, 10});
        }
    };
}