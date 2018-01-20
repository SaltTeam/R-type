//
// Created by vivaldi91 on 18/01/18.
//

#pragma once

#include <entities/weapons/sub/Laser2.hpp>
#include "entities/ships/Ship.hpp"

namespace Entities {
    class TieBomber : public Ship {
    private:
        short turnCheck;
        std::uniform_int_distribution<std::mt19937::result_type> dist10;
        std::mt19937 rng;

    public:
        TieBomber(SCOPE *scope, uint64_t id = 0, bool isEnabled = true, const float &x = 0, const float &y = 0)
                : Ship(scope, id, "resources/sprites/ships/enemy/ship3/base.png", isEnabled, Entities::Ship::GAME, x,
                       y, 0.25, 0.05, 40) {
            this->weapon = new Entities::Laser2(scope, this->team);
            this->weapon->setYSpeed(-(this->weapon->getYSpeed()));
            this->turnCheck = 0;
            this->canons.push_back({this->texture->sprite.getGlobalBounds().width / 2, this->texture->sprite.getGlobalBounds().height / 2 + 30});
            this->rng.seed(std::random_device()());
            std::uniform_int_distribution<std::mt19937::result_type> dist6(1,10000);
            dist10 = dist6;
        }

        void update() override {
            int random_variable = std::rand();
            this->move();
            if (dist10(rng) % 510 == 0)
                this->shoot();
            this->turnCheck += 1;
            Ship::update();
            if (this->turnCheck == 1000 || this->position.x + this->texture->sprite.getGlobalBounds().width > this->scope->gameService->getWindowSize().x - 15 || this->position.x + this->texture->sprite.getGlobalBounds().width < 15) {
                this->speed.x = -(this->speed.x);
                this->turnCheck = 0;
            }
        }

    };
}