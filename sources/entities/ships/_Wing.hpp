//
// Created by delacr_a on 15/01/18.
//

#pragma once

#include "entities/PlayerShip.hpp"

namespace Entities {
    class _Wing : public PlayerShip {
    public:
	_Wing(SCOPE *scope, uint16_t id, bool isEnabled, const float &x, const float &y)
	    : PlayerShip(scope, id, "resources/sprites/ships/player/ship5/base.png", isEnabled, x, y, 0.15, 0.15) {};
    };
}