//
// Created by vivaldi91 on 17/01/18.
//

#pragma once

#include <entities/weapons/sub/Laser2.hpp>
#include <entities/weapons/sub/Laser1.hpp>
#include "entities/ships/Ship.hpp"

namespace Entities {
    class TieAvenger : public Ship {
    private:
        float originXSpeed;
        float originYSpeed;
        std::uniform_int_distribution<std::mt19937::result_type> dist10;
        std::mt19937 rng;

    public:
        TieAvenger(SCOPE *scope, uint64_t id, network::protocol::PlayerColor playerColor,
                   network::protocol::Update updateType = network::protocol::Update::Replica,
                   uint16_t refreshTime = 1000,
                   bool isEnabled = true, const float &x = 0, const float &y = 0)
                : Ship(scope, id, playerColor, updateType, refreshTime, isEnabled, Entities::Ship::GAME, x, y, 0.2, 0.2,
                       40) {
            this->registerTexture("resources/sprites/ships/enemy/ship2/base.png");
            this->weapon = new Entities::Laser1(scope, this->team);
            this->weapon->setYSpeed(-(this->weapon->getYSpeed()));
            this->originXSpeed = 0.2;
            this->originYSpeed = 0.2;
            this->canons.push_back({this->texture->sprite.getGlobalBounds().width / 2 - 5,
                                    this->texture->sprite.getGlobalBounds().height / 2 - 2});
            this->canons.push_back({this->texture->sprite.getGlobalBounds().width / 2 + 5,
                                    this->texture->sprite.getGlobalBounds().height / 2 - 2});
            this->rng.seed(std::random_device()());
            std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 10000);
            dist10 = dist6;
        }

        void update() override {
            int random_variable = std::rand();
            this->move();
            if (dist10(rng) % 1005 == 0)
                this->shoot();
            Ship::update();
            if ((this->position.x >= (this->scope->gameService->getWindowSize().x / 2) &&
                 this->speed.x == this->originXSpeed
                 && this->speed.y == this->originYSpeed) ||
                (this->position.x <= (this->scope->gameService->getWindowSize().x / 2) &&
                 this->speed.x != this->originXSpeed
                 && this->speed.y == this->originYSpeed))
                this->speed.y = -(this->speed.y);
            else if ((this->position.x >= (this->scope->gameService->getWindowSize().x - 50) &&
                      (this->speed.x == this->originXSpeed && this->speed.y != this->originYSpeed)) ||
                     (this->position.x <= 25 &&
                      (this->speed.x != this->originXSpeed && this->speed.y != this->originYSpeed))) {
                this->speed.y = -(this->speed.y);
                this->speed.x = -(this->speed.x);
            }
        }

    };
}