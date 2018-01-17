//
// Created by delacr_a on 17/01/18.
//

#pragma once

#include <SFML/Window.hpp>

namespace Entities {
    class IWeapon {
    public:
        virtual void shoot(std::vector<sf::Vector2f> const &canons, sf::Vector2f const &position) = 0;

    protected:
        virtual void spawnLasers(sf::Vector2f const &position) = 0;
    };
}
