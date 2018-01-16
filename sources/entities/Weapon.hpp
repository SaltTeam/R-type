//
// Created by delacr_a on 12/01/18.
//

#pragma once

#include "engine/ForwardDeclaration.hpp"
#include <chrono>

namespace Entities {
    class Weapon {
    public:

	void shoot(sf::Vector2f const &position);

	void shoot(std::vector<sf::Vector2f> const &positions);

    protected:
	Weapon(SCOPE *scope, std::string const &projectilePath, float const &cd, int const &damage,
	       float const &xSpeed, float const &ySpeed, uint64_t const &originId);
	SCOPE *scope;
	float cd;
	int damage;
	std::chrono::time_point<std::chrono::system_clock> lastUse;
	std::string projectilePath;
	float xSpeed;
	float ySpeed;
	uint64_t originId;

    private:
	void spawnLasers(sf::Vector2f const &position);
	void spawnAsteroids(sf::Vector2f const &position);
    };
}