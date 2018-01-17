
#pragma once

#include "engine/entity/MovableEntity.hpp"
#include "entities/weapons/Weapon.hpp"

namespace Entities {
    class PlayerShip : public MOVABLE_ENTITY {
    public:
        void takeDamage(int const &value);

    protected:
        PlayerShip(SCOPE *scope, uint64_t id, const std::string &texturePath, bool isEnabled,
                   float const &x, float const &y, float const &xSpeed, float const &ySpeed,
                   int const &health, int const &shield = 0);

        ~PlayerShip() {
            delete this->weapon;
        }

        void update() override;

        void shoot();

        void registerBindings();

        void onCollision(ENTITY *other);

        IWeapon *weapon;

        std::vector<sf::Vector2f> canons;

        int health;

        int shield;
    };
}
