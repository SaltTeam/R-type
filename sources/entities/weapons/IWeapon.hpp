//
// Created by delacr_a on 17/01/18.
//

#pragma once

#include <SFML/Window.hpp>
#include "entities/powerups/grade.hpp"

namespace Entities {
    class IWeapon {
    public:
        virtual bool shoot(std::vector<sf::Vector2f> const &canons, sf::Vector2f const &position) = 0;

        virtual void setSpeed(sf::Vector2f const &speed) = 0;

        virtual void setXSpeed(float const &xSpeed) = 0;

        virtual void setYSpeed(float const &ySpeed) = 0;

        virtual void setCd(float const &value) = 0;

        virtual void setLastUse(std::chrono::time_point<std::chrono::system_clock> time) = 0;

        virtual sf::Vector2f getSpeed() const = 0;

        virtual float getXSpeed() const = 0;

        virtual float getYSpeed() const = 0;

        virtual void upgrade(GRADE grade) = 0;

    protected:
        virtual void spawnLasers(sf::Vector2f const &position) = 0;
    };
}
