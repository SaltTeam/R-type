//
// Created by vivaldi91 on 18/01/18.
//

#pragma once

#include <entities/weapons/sub/Laser1.hpp>
#include "entities/ships/Ship.hpp"

namespace Entities {
    class TieExperiment : public Ship {
    private:
        std::uniform_int_distribution<std::mt19937::result_type> dist10;
        std::mt19937 rng;

    public:
        TieExperiment(SCOPE *scope, uint64_t id, network::protocol::PlayerColor playerColor,
                      network::protocol::Update updateType = network::protocol::Update::Replica,
                      uint16_t refreshTime = 30,
                      bool isEnabled = true, const float x = 0, const float y = 0)
                : Ship(scope, id, playerColor, updateType, refreshTime, isEnabled, Entities::Ship::GAME, x, y, 0.15,
                       0.15, 40) {
            this->registerTexture("resources/sprites/ships/enemy/ship5/base.png");
            this->type = network::protocol::Type::SHIP_TIEEXPERIMENT;
            this->weapon = new Entities::Laser1(scope, this->team);
            this->weapon->setYSpeed(-(this->weapon->getYSpeed()));
            this->canons.push_back({this->texture->sprite.getGlobalBounds().width / 2 - 5,
                                    this->texture->sprite.getGlobalBounds().height / 2 - 20});
            this->canons.push_back({this->texture->sprite.getGlobalBounds().width / 2 + 5,
                                    this->texture->sprite.getGlobalBounds().height / 2 - 20});
            this->rng.seed(std::random_device()());
            std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 100000);
            dist10 = dist6;
        }

        void update() override {
            int random_variable = std::rand();
            this->move();
            if (dist10(rng) % 1005 == 0)
                this->shoot();
            Ship::update();
            if (this->position.x < 10 + this->texture->sprite.getGlobalBounds().width)
                this->speed.x = 0.15;
            if (this->position.x + this->texture->sprite.getGlobalBounds().width >
                this->scope->gameService->getWindowSize().x - 50)
                this->speed.x = -0.15;
            if (this->position.y < 10 + this->texture->sprite.getGlobalBounds().height)
                this->speed.y = 0.15;
            if (this->position.y + this->texture->sprite.getGlobalBounds().height >
                this->scope->gameService->getWindowSize().y - 50)
                this->speed.y = -0.15;
            if (dist10(rng) % 2765 == 0)
                this->speed.x = -(this->speed.x);
            if (dist10(rng) % 9845 == 0)
                this->speed.y = -(this->speed.y);
        }

    };
}
