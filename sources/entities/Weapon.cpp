//
// Created by delacr_a on 12/01/18.
//

#include <ctime>
#include <engine/scope/Scope.hpp>
#include "Weapon.hpp"
#include "Projectile.hpp"

Entities::Weapon::Weapon(SCOPE *scope, float const &cd, int const &damage)
  : scope(scope), cd(cd), damage(damage), lastUse(time(nullptr)) {}

void Entities::Weapon::shoot(sf::Vector2f const &position) {
  if (difftime(time(nullptr), this->lastUse) >= this->cd) {
    time(&this->lastUse);
    this->scope->entityManager.add<Entities::Projectile>(LAYER::Layer1, this->scope, 0,
							 "resources/sprites/Lasers/laserRed01.png", true, position.x,
							 position.y);
  }
}

void Entities::Weapon::shoot(std::vector<sf::Vector2f> const &positions) {
  if (difftime(time(nullptr), this->lastUse) >= this->cd) {
    time(&this->lastUse);
    for (auto it : positions)
      this->scope->entityManager.add<Entities::Projectile>(LAYER::Layer1, this->scope, 0,
							   "resources/sprites/Lasers/laserRed01.png", true, it.x, it.y);
  }
}