
#pragma once

#include "engine/entity/MovableEntity.hpp"
#include "Ship.hpp"

namespace Entities {
    class PlayerShip : public Ship {

    protected:
        PlayerShip(SCOPE *scope, uint64_t id,network::protocol::PlayerColor playerColor, network::protocol::Update updateType, uint16_t refreshTime, bool isEnabled,
                   float const &x, float const &y, float const &xSpeed, float const &ySpeed,
                   int const &health, int const &shield = 0);


        void registerBindings();

        virtual void onCollision(ENTITY *other);

        std::string getColorString();
    };
}
