//
// Created by delacr_a on 16/01/18.
//

#pragma once

#include "entities/weapons/Weapon.hpp"

namespace Entities {
    class Laser1 : public Weapon {
    public:
        Laser1(SCOPE *scope, uint64_t const &originId)
                : Weapon(scope, "resources/sprites/Lasers/laserRed01.png", 0.5, 10, 0, -0.5, originId) {}
    };
}
