//
// Created by delacr_a on 12/01/18.
//

#pragma once

#include "engine/ForwardDeclaration.hpp"
#include "IWeapon.hpp"
#include "AWeapon.hpp"
#include <chrono>

namespace Entities {
    class Weapon : public AWeapon {
    public:
        virtual void shoot(std::vector<sf::Vector2f> const &canons, sf::Vector2f const &position);

    protected:
        Weapon(SCOPE *scope, std::string const &projectilePath, float const &cd, int const &damage,
               float const &xSpeed, float const &ySpeed, uint64_t const &originId)
                : AWeapon(scope, projectilePath, cd, damage, xSpeed, ySpeed, originId) {};

        virtual void spawnLasers(sf::Vector2f const &position);

    };
}