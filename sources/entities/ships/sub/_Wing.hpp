//
// Created by delacr_a on 15/01/18.
//

#pragma once

#include "entities/weapons/sub/Laser1.hpp"
#include "entities/ships/PlayerShip.hpp"

namespace Entities {
    class _Wing : public PlayerShip {
    public:
        _Wing(SCOPE *scope, uint64_t id, network::protocol::PlayerColor playerColor,
              network::protocol::Update updateType = network::protocol::Update::Replica, uint16_t refreshTime = 5,
              bool isEnabled = true, const float x = 0, const float y = 0)
                : PlayerShip(scope, id, playerColor, updateType, refreshTime, isEnabled, x, y, 0.25, 0.25, 200) {
            this->registerTexture("resources/sprites/ships/player/ship5/" + this->getColorString() + ".png");
            this->type = network::protocol::Type::SHIP_WING;
            this->weapon = new Entities::Laser1(scope, this->team);
            this->canons.push_back({2, -15});
            this->canons.push_back({114, -15});
            if (x == 0 && y == 0)
                this->setPosition(static_cast<short>(this->playerColor) * 100,
                                  this->scope->gameService->getWindowSize().y - this->texture->sprite.getGlobalBounds().height);
        };
    };
}