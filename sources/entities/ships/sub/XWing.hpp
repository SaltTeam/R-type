//
// Created by delacr_a on 15/01/18.
//

#pragma once

#include "entities/weapons/sub/Laser1.hpp"
#include "entities/ships/PlayerShip.hpp"

namespace Entities {
    class XWing : public PlayerShip {
    public:
		XWing(SCOPE *scope, uint64_t id = 0, network::protocol::Update updateType = network::protocol::Update::Replica, uint16_t refreshTime = 1000,
			  bool isEnabled = true, const float &x = 0, const float &y = 0)
				: PlayerShip(scope, id, updateType, refreshTime, isEnabled, x, y, 0.25, 0.25, 100) {
			this->registerTexture("resources/sprites/ships/player/ship1/base.png");
			this->type = network::protocol::Type::SHIP_XWING;
			this->weapon = new Entities::Laser1(scope, this->team);
			this->canons.push_back({2, 0});
			this->canons.push_back({77, 0});
		};
    };
}