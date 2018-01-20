//
// Created by delacr_a on 19/01/18.
//

#pragma once

#include <engine/scope/Scope.hpp>
#include "Asteroid.hpp"

namespace Entities {
    class TinyAsteroid : public Asteroid {
    public:
        TinyAsteroid(SCOPE *scope, uint64_t id, bool isEnabled, float const &x, float const &y)
                : Asteroid(scope, id, "resources/sprites/Meteors/meteorGrey_small2.png", isEnabled, x, y) {
            this->type = network::protocol::Type::ASTEROID_TINY;
        }
    };
}