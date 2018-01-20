//
// Created by delacr_a on 15/01/18.
//

#pragma once

#include "entities/weapons/sub/Laser4.hpp"
#include "entities/ships/PlayerShip.hpp"

namespace Entities {
    class Arc : public PlayerShip {
    public:
        Arc(SCOPE *scope, uint64_t id = 0, network::protocol::Update updateType = network::protocol::Update::Replica, uint16_t refreshTime = 1000,
            bool isEnabled = true, const float &x = 0, const float &y = 0)
                : PlayerShip(scope, id, updateType, refreshTime, isEnabled, x, y, 0.3, 0.3, 125, 50) {
            this->registerTexture("resources/sprites/ships/player/ship3/base.png");
            this->weapon = new Entities::Laser4(scope, this->team);
            this->canons.push_back({3, 0});
            this->canons.push_back({151, 0});
        };
    };
}