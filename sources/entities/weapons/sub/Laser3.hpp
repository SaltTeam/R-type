//
// Created by delacr_a on 16/01/18.
//

#pragma once

#include "entities/weapons/Weapon.hpp"

namespace Entities {
    class Laser3 : public Weapon {
    public:
        Laser3(SCOPE *scope, Entities::Ship::TEAM originTeam)
                : Weapon(scope, "resources/sprites/Lasers/laserRed02.png", 0.3, 7, 0, -0.8f, originTeam, network::protocol::Type::LASER3) {}
    };
}
