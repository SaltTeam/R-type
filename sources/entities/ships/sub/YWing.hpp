//
// Created by delacr_a on 15/01/18.
//

#pragma once

#include "entities/weapons/sub/Laser2.hpp"
#include "entities/ships/PlayerShip.hpp"

namespace Entities {
    class YWing : public PlayerShip {
    public:
		YWing(SCOPE *scope, uint64_t id = 0, network::protocol::Update updateType = network::protocol::Update::Replica, uint16_t refreshTime = 1000,
			  bool isEnabled = true, const float &x = 0, const float &y = 0)
				: PlayerShip(scope, id, updateType, refreshTime, isEnabled, x, y, 0.15, 0.15, 200) {
			this->registerTexture("resources/sprites/ships/player/ship2/base.png");
			this->type = network::protocol::Type::SHIP_YWING;
			this->weapon = new Entities::Laser2(scope, this->team);
			this->canons.push_back({this->texture->sprite.getGlobalBounds().width / 2, -8});
		};
    };
}