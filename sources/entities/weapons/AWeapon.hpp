//
// Created by delacr_a on 17/01/18.
//

#pragma once

#include <SFML/Window.hpp>
#include <engine/ForwardDeclaration.hpp>
#include <chrono>
#include "IWeapon.hpp"

namespace Entities {
    class AWeapon : public IWeapon {
    public:
        virtual void shoot(std::vector<sf::Vector2f> const &canons, sf::Vector2f const &position) = 0;

    protected:
        AWeapon(SCOPE *scope, std::string const &projectilePath, float const &cd, int const &damage,
                float const &xSpeed, float const &ySpeed, uint64_t const &originId)
                : scope(scope), projectilePath(projectilePath), cd(cd), damage(damage), xSpeed(xSpeed), ySpeed(ySpeed),
                  originId(originId) {
            this->lastUse = std::chrono::system_clock::from_time_t(0);
        };

        virtual void spawnLasers(sf::Vector2f const &position) = 0;

        SCOPE *scope;
        float cd;
        int damage;
        std::chrono::time_point<std::chrono::system_clock> lastUse;
        std::string projectilePath;
        float xSpeed;
        float ySpeed;
        uint64_t originId;
    };
}
