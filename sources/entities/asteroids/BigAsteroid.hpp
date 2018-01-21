//
// Created by delacr_a on 19/01/18.
//

#pragma once

#include <engine/scope/Scope.hpp>
#include "MedAsteroid.hpp"

namespace Entities {
    class BigAsteroid : public Asteroid {
    public:
        BigAsteroid(SCOPE *scope, uint64_t id, network::protocol::PlayerColor playerColor, bool isEnabled,
                    float const x, float const y)
                : Asteroid(scope, id, playerColor, "resources/sprites/Meteors/meteorGrey_big2.png", isEnabled, x, y) {
            this->type = network::protocol::Type::ASTEROID_BIG;
                
                }

        ~BigAsteroid() override {
            if (playerColor == network::protocol::PlayerColor::Blue)
            {
                for (int i = 0; i < 2; ++i) {
                    this->scope->entityManager.add<Entities::MedAsteroid>(LAYER::Layer1, true,
                                                                          this->position.x +
                                                                          this->texture->sprite.getGlobalBounds().width / 2,
                                                                          this->position.y +
                                                                          this->texture->sprite.getGlobalBounds().height /
                                                                          2);
                }
            }
        }
    };
}