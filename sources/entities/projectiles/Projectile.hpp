//
// Created by delacr_a on 12/01/18.
//

#pragma once

#include <entities/ships/Ship.hpp>
#include "engine/ForwardDeclaration.hpp"
#include "engine/scope/Scope.hpp"
#include "engine/entity/Entity.hpp"
#include "engine/entity/MovableEntity.hpp"

namespace Entities {
    class Projectile : public MOVABLE_ENTITY {
    public:
        Projectile(SCOPE *scope, uint64_t id, const std::string &texturePath, bool isEnabled,
                   float const &x, float const &y, float const &xSpeed, float const &ySpeed,
                   int const &damage, Entities::Ship::TEAM originTeam);

        virtual void update() override;

        void onCollision(ENTITY *other);

        int damage;

        Entities::Ship::TEAM originTeam;
    };
}