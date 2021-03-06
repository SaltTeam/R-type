//
// Created by delacr_a on 16/01/18.
//

#pragma once

#include <entities/ships/Ship.hpp>
#include "entities/weapons/Weapon.hpp"

namespace Entities {
    class Laser1 : public Weapon {
    public:
        Laser1(SCOPE *scope, Entities::Ship::TEAM originTeam)
                : Weapon(scope, "resources/sprites/Lasers/laser" + getColorOfProjectile(originTeam) + "01.png", 0.4, 15, 0, -0.6f, originTeam, network::protocol::Type::LASER1) {}
    };
}
