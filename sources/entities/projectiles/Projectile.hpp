//
// Created by delacr_a on 12/01/18.
//

#pragma once

#include "engine/ForwardDeclaration.hpp"
#include "entities/ships/Ship.hpp"
#include "engine/scope/Scope.hpp"
#include "engine/entity/Entity.hpp"
#include "engine/entity/MovableEntity.hpp"

namespace Entities {
    class Projectile : public MOVABLE_ENTITY {
    public:
        Projectile(SCOPE *scope, uint64_t id,network::protocol::PlayerColor playerColor, network::protocol::Update updateType,
                   std::string const &texturePath, bool isEnabled,
                   float const x, float const y, float const xSpeed, float const ySpeed,
                   int const damage, Entities::Ship::TEAM originTeam, network::protocol::Type typeUpdate);

        void update() override;

        void onCollision(ENTITY *other);

        int damage;

        Entities::Ship::TEAM originTeam;
    };
}