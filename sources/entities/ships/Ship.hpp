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
        friend NET_SERVICE;

    public:
        enum TEAM : short {
            PLAYER,
            GAME
        };

    public:
        virtual bool shoot();

        void takeDamage(int value);

        void gainHealth(GRADE grade);

        void gainShield(GRADE grade);

        void upgradeWeapon(GRADE grade);

        void gainSpeed(GRADE grade);

        TEAM getTeam();

        virtual int getShield();

    protected:
        Ship(SCOPE *scope, uint64_t id, network::protocol::Update updateType, uint16_t refreshTime, bool isEnabled,
             TEAM team, float const &x, float const &y, float const &xSpeed, float const &ySpeed,
             int const &health, int const &shield = 0);

        ~Ship() override;

        void update() override;

        void moveUp() override;

        void moveDown() override;

        void moveRight() override;

        void moveLeft() override;

        void spawnPowerUp();

        virtual void onCollision(ENTITY *other);

        void registerTexture(std::string const &path);

        IWeapon *weapon;

        std::vector<sf::Vector2f> canons;

        int health;

        int maxHealth;

        int shield;

        TEAM team;
    };
}
