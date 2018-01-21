//
// Created by delacr_a on 16/01/18.
//

#pragma once

#include "entities/weapons/Weapon.hpp"

namespace Entities {
    class Laser2 : public Weapon {
    public:
        Laser2(SCOPE *scope, Entities::Ship::TEAM originTeam)
                : Weapon(scope, "resources/sprites/Lasers/laser" + getColorOfProjectile(originTeam) + "08.png", 0.5, 35, 0, -0.4f, originTeam, network::protocol::Type::LASER2) {}
    };
}
