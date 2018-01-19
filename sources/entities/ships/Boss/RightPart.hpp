//
// Created by delacr_a on 19/01/18.
//

#pragma once

#include "entities/weapons/sub/Laser1.hpp"
#include "entities/ships/Ship.hpp"

namespace Entities {
    class RightPart : public Ship {
    public:
        RightPart(SCOPE *scope, uint64_t id = 0, bool isEnabled = true, const float &x = 0, const float &y = 0)
                : Ship(scope, id, "resources/sprites/Boss/right-part.png", isEnabled, Entities::Ship::GAME, x,
                       y, 0, 0, 500, 1) {
            this->weapon = new Entities::Laser1(scope, this->team);
            this->weapon->setYSpeed(1);
            this->weapon->setCd(0.75);
            this->canons.push_back({this->texture->sprite.getGlobalBounds().width / 2 - 5,
                                    this->texture->sprite.getGlobalBounds().height / 2 + 30});
            this->canons.push_back({this->texture->sprite.getGlobalBounds().width - 20,
                                    this->texture->sprite.getGlobalBounds().height / 2 + 30});
        }

        void update() override {
            if (this->shoot())
            {
                if (this->canons.size() == 2)
                {
                    delete this->weapon;
                    this->weapon = new Entities::Laser2(scope, this->team);
                    this->weapon->setYSpeed(1);
                    this->weapon->setCd(0.75);
                    this->weapon->setLastUse(std::chrono::system_clock::now());
                    this->canons.clear();
                    this->canons.push_back({this->texture->sprite.getGlobalBounds().width / 2 + 30,
                                            this->texture->sprite.getGlobalBounds().height / 2 + 30});
                }
                else{
                    delete this->weapon;
                    this->weapon = new Entities::Laser1(scope, this->team);
                    this->weapon->setYSpeed(1);
                    this->weapon->setCd(0.75);
                    this->weapon->setLastUse(std::chrono::system_clock::now());
                    this->canons.clear();
                    this->canons.push_back({80, this->texture->sprite.getGlobalBounds().height / 2 + 30});
                    this->canons.push_back({this->texture->sprite.getGlobalBounds().width - 20,
                                            this->texture->sprite.getGlobalBounds().height / 2 + 30});
                }
            }
            Ship::update();
        }

    };
}