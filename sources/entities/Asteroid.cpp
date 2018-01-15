//
// Created by delacr_a on 11/01/18.
//

#include "Asteroid.hpp"

Entities::Asteroid::Asteroid(SCOPE *scope, uint64_t id, const std::string &texturePath, bool isEnabled,
			     const float &x, const float &y)
:MovableEntity(scope, id, isEnabled, x, y)
{
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<float> dist(-0.2, 0.2);

  this->setTexture(texturePath);
  this->setSpeed(dist(mt), dist(mt));
}

void Entities::Asteroid::update() {
  this->move();
}