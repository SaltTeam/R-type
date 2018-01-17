//
// Created by delacr_a on 15/01/18.
//

#pragma once

#include "entities/weapons/sub/Laser4.hpp"
#include "entities/ships/PlayerShip.hpp"

namespace Entities {
    class Arc : public PlayerShip {
    public:
		Arc(SCOPE *scope, uint64_t id = 0, bool isEnabled = true, const float &x = 0, const float &y = 0)
				: PlayerShip(scope, id, "resources/sprites/ships/player/ship3/base.png", isEnabled, x, y, 0.25, 0.25,
							 100) {
			this->weapon = new Entities::Laser4(scope, id);
			this->canons.push_back({3, 0});
			this->canons.push_back({151, 0});
		};
    };
}