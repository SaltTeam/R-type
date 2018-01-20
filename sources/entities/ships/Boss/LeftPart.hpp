//
// Created by delacr_a on 19/01/18.
//

#pragma once

#include "entities/asteroids/BigAsteroid.hpp"
#include "entities/weapons/sub/Laser1.hpp"
#include "entities/ships/Ship.hpp"

namespace Entities {
    class LeftPart : public Ship {
    public:
        LeftPart(SCOPE *scope, uint64_t id = 0, network::protocol::Update updateType = network::protocol::Update::Replica, uint16_t refreshTime = 1000,
                 bool isEnabled = true, const float &x = 0, const float &y = 0)
                : Ship(scope, id, updateType, refreshTime, isEnabled, Entities::Ship::GAME, x, y, 0, 0, 500) {
            this->registerTexture("resources/sprites/Boss/left-part.png");
            this->secondWeapon = false;
            this->weapon = new Entities::Laser1(scope, this->team);
            this->weapon->setYSpeed(1);
            this->weapon->setCd(0.75);
            this->weapon2 = new Entities::Laser2(scope, this->team);
            this->weapon2->setYSpeed(1);
            this->weapon2->setCd(0.75);
            this->canons.push_back({20, this->texture->sprite.getGlobalBounds().height / 2 + 40});
            this->canons.push_back({this->texture->sprite.getGlobalBounds().width / 2 + 5,
                                    this->texture->sprite.getGlobalBounds().height / 2 + 30});
            this->canons2.push_back({this->texture->sprite.getGlobalBounds().width / 2 - 30,
                                     this->texture->sprite.getGlobalBounds().height / 2 + 30});
        }

        ~LeftPart() override {
            delete this->weapon2;
            for (int i = 0; i < 4; ++i) {
                this->scope->entityManager.add<Entities::BigAsteroid>(LAYER::Layer1, true,
                                                                   this->position.x + this->texture->sprite.getGlobalBounds().width / 2,
                                                                   this->position.y + this->texture->sprite.getGlobalBounds().height / 2);
            }
        }

        bool shoot() override {
            if (this->secondWeapon)
                return this->weapon2->shoot(this->canons2, this->position);
            else
                return this->weapon->shoot(this->canons, this->position);
        }

        void update() override {
            if (this->shoot()) {
                this->secondWeapon = !this->secondWeapon;
                if (this->secondWeapon)
                    this->weapon2->setLastUse(std::chrono::system_clock::now());
                else
                    this->weapon->setLastUse(std::chrono::system_clock::now());
            }
            Ship::update();
        }

        int getShield() override {
            return 1;
        }

    protected:
        IWeapon *weapon2;
        bool secondWeapon;
        std::vector<sf::Vector2f> canons2;
    };
}