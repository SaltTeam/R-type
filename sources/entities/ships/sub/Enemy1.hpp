//
// Created by delacr_a on 17/01/18.
//

#pragma once

#include <entities/weapons/sub/Laser1.hpp>
#include <entities/weapons/sub/Laser4.hpp>
#include "entities/ships/Ship.hpp"

namespace Entities {
    class Enemy1 : public Ship {
    public:
        Enemy1(SCOPE *scope, uint64_t id = 0, bool isEnabled = true, const float &x = 0, const float &y = 0)
                : Ship(scope, id, "resources/sprites/ships/enemy/ship1/base.png", isEnabled, Entities::Ship::GAME, x,
                       y, 0.25, 0.01, 50) {
            this->weapon = new Entities::Laser4(scope, this->team);
            this->weapon->setYSpeed(-(this->weapon->getYSpeed()));
            this->weapon->setCd(1);
            this->canons.push_back({this->texture->sprite.getGlobalBounds().width / 2 - 5, this->texture->sprite.getGlobalBounds().height / 2 + 2});
            this->canons.push_back({this->texture->sprite.getGlobalBounds().width / 2 + 5, this->texture->sprite.getGlobalBounds().height / 2 + 2});
        }

        void update() override {
            this->move();
            this->shoot();
            Ship::update();
            if (this->position.x <= 0 || this->position.x + this->texture->sprite.getGlobalBounds().width >= this->scope->gameService->getWindowSize().x)
                this->speed.x = -(this->speed.x);
        }

    };
}