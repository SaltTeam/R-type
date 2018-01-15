//
// Created by delacr_a on 12/01/18.
//

#include "Projectile.hpp"

Entities::Projectile::Projectile(SCOPE *scope, uint64_t id, const std::string &texturePath, bool isEnabled,
				 const float &x, const float &y)
  :MovableEntity(scope, id, isEnabled, x, y)
{
  this->setTexture(texturePath);
  this->setSpeed(0, -0.4);
}

void Entities::Projectile::update() {
  this->move();
}