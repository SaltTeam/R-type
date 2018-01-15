//
// Created by delacr_a on 15/01/18.
//

#pragma once

#include "entities/PlayerShip.hpp"

namespace Entities {
    class Arc : public PlayerShip {
    public:
	Arc(SCOPE *scope, uint16_t id, bool isEnabled, const float &x, const float &y)
	    : PlayerShip(scope, id, "resources/sprites/ships/player/ship3/base.png", isEnabled, x, y, 0.25, 0.25) {};
    };
}