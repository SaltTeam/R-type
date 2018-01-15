//
// Created by delacr_a on 12/01/18.
//

#pragma once

#include "engine/ForwardDeclaration.hpp"

namespace Entities {
    class Weapon {
    public:
	Weapon(SCOPE *scope, float const &cd = 0.5, int const &damage = 10);

	void shoot(sf::Vector2f const &position);

	void shoot(std::vector<sf::Vector2f> const &positions);

    protected:
	SCOPE *scope;
	float cd;
	int damage;
	std::chrono::time_point<std::chrono::system_clock> lastUse;

    private:
	void spawnLasers(sf::Vector2f const &position);
	void spawnAsteroids(sf::Vector2f const &position);
    };
}