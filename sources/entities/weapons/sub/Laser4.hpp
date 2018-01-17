//
// Created by delacr_a on 16/01/18.
//

#pragma once

#include <SFML/Window.hpp>
#include "entities/weapons/Weapon.hpp"

namespace Entities {
    class Laser4 : public AWeapon {
    public:
        Laser4(SCOPE *scope, Entities::Ship::TEAM originTeam)
                : AWeapon(scope, "resources/sprites/Lasers/laserRed11.png", 0.25, 5, 0, -0.3, originTeam) {}

        virtual void shoot(std::vector<sf::Vector2f> const &canons, sf::Vector2f const &position);

    protected:
        virtual void spawnLasers(sf::Vector2f const &position);
    };
}
