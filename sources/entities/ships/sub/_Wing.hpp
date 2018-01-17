//
// Created by delacr_a on 15/01/18.
//

#pragma once

#include "entities/weapons/sub/Laser1.hpp"
#include "entities/ships/PlayerShip.hpp"

namespace Entities {
    class _Wing : public PlayerShip {
    public:
        _Wing(SCOPE *scope, uint64_t id = 0, bool isEnabled = true, const float &x = 0, const float &y = 0)
                : PlayerShip(scope, id, "resources/sprites/ships/player/ship5/base.png", isEnabled, x, y, 0.15, 0.15,
                             100) {
            this->weapon = new Entities::Laser1(scope, id);
            this->canons.push_back({2, -15});
            this->canons.push_back({114, -15});
        };
    };
}