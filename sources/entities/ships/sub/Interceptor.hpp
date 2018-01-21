//
// Created by delacr_a on 15/01/18.
//

#pragma once

#include "entities/weapons/sub/Laser3.hpp"
#include "entities/ships/PlayerShip.hpp"

namespace Entities {
    class Interceptor : public PlayerShip {
    public:
        Interceptor(SCOPE *scope, uint64_t id, network::protocol::PlayerColor playerColor,
                    network::protocol::Update updateType = network::protocol::Update::Replica,
                    uint16_t refreshTime = 1000,
                    bool isEnabled = true, const float x = 0, const float y = 0)
                : PlayerShip(scope, id, playerColor, updateType, refreshTime, isEnabled, x, y, 0.3, 0.3, 75, 25) {
            this->registerTexture("resources/sprites/ships/player/ship4/" + this->getColorString() + ".png");
            this->type = network::protocol::Type::SHIP_INTERCEPTOR;
            this->weapon = new Entities::Laser3(scope, this->team);
            this->canons.push_back({this->texture->sprite.getGlobalBounds().width / 2 - 5,
                                    this->texture->sprite.getGlobalBounds().height / 2 - 42});
            this->canons.push_back({this->texture->sprite.getGlobalBounds().width / 2 + 5,
                                    this->texture->sprite.getGlobalBounds().height / 2 - 42});
            if (x == 0 && y == 0)
                this->setPosition(static_cast<short>(this->playerColor) * 100,
                                  this->scope->gameService->getWindowSize().y - this->texture->sprite.getGlobalBounds().height);
        };
    };
}