//
// Created by delacr_a on 12/01/18.
//

#pragma once

#include "engine/ForwardDeclaration.hpp"
#include "IWeapon.hpp"
#include "AWeapon.hpp"
#include <chrono>
#include <entities/ships/Ship.hpp>

namespace Entities {
    class Weapon : public AWeapon {
    public:
        virtual bool shoot(std::vector<sf::Vector2f> const &canons, sf::Vector2f const &position);

    protected:
        Weapon(SCOPE *scope, std::string const &projectilePath, float const &cd, int const &damage,
               float const &xSpeed, float const &ySpeed, Entities::Ship::TEAM originTeam)
                : AWeapon(scope, projectilePath, cd, damage, xSpeed, ySpeed, originTeam) {};

        virtual void spawnLasers(sf::Vector2f const &position);

    };
}