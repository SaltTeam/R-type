//
// Created by delacr_a on 16/01/18.
//

#pragma once

#include "entities/weapons/Weapon.hpp"

namespace Entities {
    class Laser2 : public Weapon {
    public:
        Laser2(SCOPE *scope, uint64_t const &originId)
                : Weapon(scope, "resources/sprites/Lasers/laserRed08.png", 0.5, 20, 0, -0.3, originId) {}
    };
}
