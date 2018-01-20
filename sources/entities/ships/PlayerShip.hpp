
#pragma once

#include "engine/entity/MovableEntity.hpp"
#include "Ship.hpp"

namespace Entities {
    class PlayerShip : public Ship {

    protected:
        PlayerShip(SCOPE *scope, uint64_t id, const std::string &texturePath, bool isEnabled,
                   float const &x, float const &y, float const &xSpeed, float const &ySpeed,
                   int const &health, int const &shield = 0);


        void registerBindings();

        virtual void onCollision(ENTITY *other);
    };
}
