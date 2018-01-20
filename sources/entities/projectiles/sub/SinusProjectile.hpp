//
// Created by delacr_a on 16/01/18.
//

#pragma once

#include <chrono>
#include "entities/projectiles/Projectile.hpp"

namespace Entities {
    class SinusProjectile : public Projectile {
    public:

        SinusProjectile(SCOPE *scope, uint64_t id, const std::string &texturePath, bool isEnabled,
                        float const &x, float const &y, float const &xSpeed, float const &ySpeed,
                        int const &damage, Entities::Ship::TEAM originTeam, network::protocol::Type type)
                : Projectile(scope, id, texturePath, isEnabled, x, y, xSpeed, ySpeed, damage, originTeam, type),
                  add(true), first(true) {
            this->lastTurn = std::chrono::system_clock::now();
        };

        virtual void update() override;

    protected:
        std::chrono::time_point<std::chrono::system_clock> lastTurn;
        bool add;
        bool first;
    };
}
