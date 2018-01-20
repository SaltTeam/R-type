//
// Created by delacr_a on 19/01/18.
//

#pragma once

#include <entities/asteroids/BigAsteroid.hpp>
#include "entities/weapons/sub/Laser2.hpp"
#include "entities/ships/Ship.hpp"

namespace Entities {
    class MiddlePart : public Ship {
    public:
        MiddlePart(SCOPE *scope, uint64_t id = 0, network::protocol::Update updateType = network::protocol::Update::Replica, uint16_t refreshTime = 1000,
                   bool isEnabled = true, const float &x = 0, const float &y = 0)
                : Ship(scope, id, updateType, refreshTime, isEnabled, Entities::Ship::GAME, x, y, 0, 0, 500) {
            this->registerTexture("resources/sprites/Boss/middle-part.png");
            this->weapon = new Entities::Laser2(scope, this->team);
            this->weapon->setYSpeed(-(this->weapon->getYSpeed()));
            this->canons.push_back({this->texture->sprite.getGlobalBounds().width / 2,
                                    this->texture->sprite.getGlobalBounds().height / 2 + 50});
        }

        ~MiddlePart() override {
            for (int i = 0; i < 4; ++i) {
                this->scope->entityManager.add<Entities::BigAsteroid>(LAYER::Layer1, this->scope, 10, true,
                                                                   this->position.x + this->texture->sprite.getGlobalBounds().width / 2,
                                                                   this->position.y + this->texture->sprite.getGlobalBounds().height / 2);
            }
        }

        int getShield() override {
            return 1;
        }

        void update() override {
            this->shoot();
            Ship::update();
        }

    };
}