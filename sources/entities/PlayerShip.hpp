
#pragma once

#include "engine/entity/MovableEntity.hpp"
#include "Weapon.hpp"

namespace Entities {
    class PlayerShip : public MOVABLE_ENTITY {
    public:
        PlayerShip(SCOPE *scope, uint64_t id, const std::string &texturePath, bool isEnabled = true,
                   float const &x = 0, float const &y = 0);

    protected:
        void update() override;

        void shoot();

        void registerBindings();

        void onCollision(ENTITY *other);

        Weapon weapon;
    };
}
