//
// Created by delacr_a on 11/01/18.
//

#pragma once

#include <random>

#include "engine/ForwardDeclaration.hpp"
#include "engine/entity/Entity.hpp"
#include "engine/entity/MovableEntity.hpp"

namespace Entities {
    class Asteroid : public MOVABLE_ENTITY {
    public:
        Asteroid(SCOPE *scope, uint64_t id, network::protocol::PlayerColor playerColor, const std::string &texturePath,
                 bool isEnabled,
                 float const &x, float const &y);

        Asteroid(SCOPE *scope, uint64_t id, network::protocol::PlayerColor playerColor, bool isEnabled,
                 float const &x, float const &y);

    protected:
        void update() override;

        void onCollision(ENTITY *other);
    };
}
