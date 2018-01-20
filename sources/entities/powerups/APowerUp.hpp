//
// Created by delacr_a on 17/01/18.
//

#pragma once

#include "engine/ForwardDeclaration.hpp"
#include "engine/entity/Entity.hpp"
#include "engine/scope/Scope.hpp"
#include "engine/entity/MovableEntity.hpp"
#include "entities/ships/PlayerShip.hpp"
#include "grade.hpp"

namespace Entities {
    class APowerUp : public MOVABLE_ENTITY {
        friend NET_SERVICE;

    public:
        APowerUp(SCOPE *scope, uint64_t id, bool isEnabled, float const &x, float const &y, float const &xSpeed,
                 float const &ySpeed, GRADE grade);

        virtual void interract(Entities::PlayerShip *ship) = 0;

        void update() override;

        void onCollision(ENTITY *other);

    protected:
        GRADE grade;
    };
}
