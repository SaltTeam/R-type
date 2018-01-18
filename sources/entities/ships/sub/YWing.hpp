//
// Created by delacr_a on 15/01/18.
//

#pragma once

#include "entities/weapons/sub/Laser2.hpp"
#include "entities/ships/PlayerShip.hpp"

namespace Entities {
    class YWing : public PlayerShip {
    public:
		YWing(SCOPE *scope, uint64_t id = 0, bool isEnabled = true, const float &x = 0, const float &y = 0)
				: PlayerShip(scope, id, "resources/sprites/ships/player/ship2/base.png", isEnabled, x, y, 0.15, 0.15,
							 200) {
			this->weapon = new Entities::Laser2(scope, this->team);
			this->canons.push_back({38, -8});
		};
    };
}