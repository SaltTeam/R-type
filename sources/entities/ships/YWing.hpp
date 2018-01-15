//
// Created by delacr_a on 15/01/18.
//

#pragma once

#include "entities/PlayerShip.hpp"

namespace Entities {
    class YWing : public PlayerShip {
    public:
	YWing(SCOPE *scope, uint16_t id, bool isEnabled, const float &x, const float &y)
	    : PlayerShip(scope, id, "resources/sprites/ships/player/ship2/base.png", isEnabled, x, y, 0.1, 0.1) {};
    };
}