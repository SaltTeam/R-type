//
// Created by delacr_a on 15/01/18.
//

#pragma once

#include "entities/weapons/Laser1.hpp"
#include "entities/PlayerShip.hpp"

namespace Entities {
    class XWing : public PlayerShip {
    public:
	XWing(SCOPE *scope, uint64_t id, bool isEnabled, const float &x, const float &y)
	    : PlayerShip(scope, id, "resources/sprites/ships/player/ship1/base.png", isEnabled, x, y, 0.2, 0.2,
			 Entities::Laser1(scope, id)) {};
    };
}