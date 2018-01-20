//
// Created by delacr_a on 15/01/18.
//

#pragma once

#include "entities/weapons/sub/Laser2.hpp"
#include "entities/ships/PlayerShip.hpp"

namespace Entities {
    class YWing : public PlayerShip {
    public:
        YWing(SCOPE *scope, uint64_t id, network::protocol::PlayerColor playerColor,
              network::protocol::Update updateType = network::protocol::Update::Replica, uint16_t refreshTime = 1000,
              bool isEnabled = true, const float &x = 0, const float &y = 0)
                : PlayerShip(scope, id, playerColor, updateType, refreshTime, isEnabled, x, y, 0.15, 0.15, 200) {
			this->type = network::protocol::Type::SHIP_YWING;
            this->registerTexture("resources/sprites/ships/player/ship2/" + this->getColorString() + ".png");
            this->weapon = new Entities::Laser2(scope, this->team);
            this->canons.push_back({this->texture->sprite.getGlobalBounds().width / 2, -8});
            if (x == 0 && y == 0)
                this->setPosition(static_cast<short>(this->playerColor) * 100,
                                  this->scope->gameService->getWindowSize().y - this->texture->sprite.getGlobalBounds().height);
        };
    };
}