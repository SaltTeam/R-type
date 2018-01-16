//
// Created by delacr_a on 15/01/18.
//

#pragma once

#include "entities/PlayerShip.hpp"

namespace Entities {
    class Intercepteur : public PlayerShip {
    public:
	Intercepteur(SCOPE *scope, uint16_t id, bool isEnabled, const float &x, const float &y)
	    : PlayerShip(scope, id, "resources/sprites/ships/player/ship4/base.png", isEnabled, x, y, 0.3, 0.3) {};
    };
}