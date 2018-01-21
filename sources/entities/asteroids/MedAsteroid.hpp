//
// Created by delacr_a on 19/01/18.
//

#pragma once

#include <engine/scope/Scope.hpp>
#include "SmallAsteroid.hpp"

namespace Entities {
    class MedAsteroid : public Asteroid {
    public:
        MedAsteroid(SCOPE *scope, uint64_t id, network::protocol::PlayerColor playerColor, bool isEnabled,
                    float const x, float const y)
                : Asteroid(scope, id, playerColor, "resources/sprites/Meteors/meteorGrey_med2.png", isEnabled, x, y) {
            this->type = network::protocol::Type::ASTEROID_MED;
                }

        ~MedAsteroid() override {
            if (NET_SERVICE::color == network::protocol::PlayerColor::Blue)
            {
                for (int i = 0; i < 2; ++i) {
                    this->scope->entityManager.add<Entities::SmallAsteroid>(LAYER::Layer1, true,
                                                                            this->position.x +
                                                                            this->texture->sprite.getGlobalBounds().width /
                                                                            2,
                                                                            this->position.y +
                                                                            this->texture->sprite.getGlobalBounds().height /
                                                                            2);
                }
            }
        }
    };
}