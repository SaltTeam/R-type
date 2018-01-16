//
// Created by delacr_a on 12/01/18.
//

#include <ctime>
#include <engine/scope/Scope.hpp>
#include <chrono>
#include "Weapon.hpp"
#include "Projectile.hpp"
#include "Asteroid.hpp"

Entities::Weapon::Weapon(SCOPE *scope, std::string const &projectilePath, float const &cd, int const &damage,
			 float const &xSpeed, float const &ySpeed, uint64_t const &originId)
    : scope(scope), projectilePath(projectilePath), cd(cd), damage(damage), xSpeed(xSpeed), ySpeed(ySpeed), originId(originId) {
    this->lastUse = std::chrono::system_clock::from_time_t(0);
}

void Entities::Weapon::shoot(std::vector<sf::Vector2f> const &canons, sf::Vector2f const &position) {
    if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now() - this->lastUse).count() >=
	this->cd) {
		for (auto &it : canons)
			this->spawnLasers(it + position);
	this->lastUse = std::chrono::system_clock::now();
    }
}

void Entities::Weapon::spawnAsteroids(sf::Vector2f const &position) {
    this->scope->entityManager.add<Entities::Asteroid>(LAYER::Layer1, this->scope, 0, true,
						       position.x, position.y);
}

void Entities::Weapon::spawnLasers(sf::Vector2f const &position) {
    this->scope->entityManager.add<Entities::Projectile>(LAYER::Layer1, this->scope, 2,
							 this->projectilePath, true,
							 position.x, position.y,
							 this->xSpeed, this->ySpeed, 10, this->originId);
}