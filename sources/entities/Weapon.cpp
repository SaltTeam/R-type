//
// Created by delacr_a on 12/01/18.
//

#include <ctime>
#include <engine/scope/Scope.hpp>
#include <chrono>
#include <iostream>
#include "Weapon.hpp"
#include "Projectile.hpp"
#include "Asteroid.hpp"

Entities::Weapon::Weapon(SCOPE *scope, float const &cd, int const &damage)
    : scope(scope), cd(cd), damage(damage) {
    this->lastUse = std::chrono::system_clock::now();
}

void Entities::Weapon::shoot(sf::Vector2f const &position) {
    if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - this->lastUse).count() >=
	this->cd) {
	this->spawnLasers(position);
	this->lastUse = std::chrono::system_clock::now();
    }
}

void Entities::Weapon::shoot(std::vector<sf::Vector2f> const &positions) {
    if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - this->lastUse).count() >=
	this->cd) {
	for (auto &it : positions)
	    this->spawnLasers(it);
	this->lastUse = std::chrono::system_clock::now();
    }
}

void Entities::Weapon::spawnAsteroids(sf::Vector2f const &position) {
    this->scope->entityManager.add<Entities::Asteroid>(LAYER::Layer1, this->scope, 0, true,
						       position.x, position.y);
}

void Entities::Weapon::spawnLasers(sf::Vector2f const &position) {
    this->scope->entityManager.add<Entities::Projectile>(LAYER::Layer1, this->scope, 0,
							 "resources/sprites/Lasers/laserRed01.png", true,
							 position.x, position.y);
}