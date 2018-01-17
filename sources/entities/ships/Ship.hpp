//
// Created by delacr_a on 17/01/18.
//

#pragma once

#include "entities/powerups/grade.hpp"
#include "engine/service/GameService.hpp"
#include "engine/entity/MovableEntity.hpp"
#include "entities/weapons/IWeapon.hpp"

namespace Entities {
    class Ship : public MOVABLE_ENTITY {
    public:
        enum TEAM {
            PLAYER,
            GAME
        };

    public:
        void shoot();

        void takeDamage(int value);

        void gainHealth(GRADE grade);

        void gainShield(GRADE grade);

        void upgradeWeapon(GRADE grade);

        void gainSpeed(GRADE grade);

        TEAM getTeam();

    protected:
        Ship(SCOPE *scope, uint64_t id, const std::string &texturePath, bool isEnabled, TEAM team,
             float const &x, float const &y, float const &xSpeed, float const &ySpeed,
             int const &health, int const &shield = 0);

        ~Ship() override {
            delete this->weapon;
        }

        void update() override;

        void moveUp() override;

        void moveDown() override;

        void moveRight() override;

        void moveLeft() override;

        void onCollision(ENTITY *other);

        IWeapon *weapon;

        std::vector<sf::Vector2f> canons;

        int health;

        int maxHealth;

        int shield;

        TEAM team;
    };
}
