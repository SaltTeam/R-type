//
// Created by delacr_a on 19/01/18.
//

#pragma once

#include <engine/scope/Scope.hpp>
#include "Asteroid.hpp"

namespace Entities {
    class TinyAsteroid : public Asteroid {
    public:
        TinyAsteroid(SCOPE *scope, uint64_t id, network::protocol::PlayerColor playerColor, bool isEnabled,
                     float const &x, float const &y)
                : Asteroid(scope, id, playerColor, "resources/sprites/Meteors/meteorGrey_small2.png", isEnabled, x,
                           y) {}
    };
}