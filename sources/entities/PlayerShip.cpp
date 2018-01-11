//
// Created by sylva on 10/01/2018.
//

#include "engine/scope/Scope.hpp"
#include "engine/service/GameService.hpp"
#include "PlayerShip.hpp"

Entities::PlayerShip::PlayerShip(SCOPE *scope, uint64_t id, const std::string &texturePath, bool isEnabled,
				 float const &x, float const &y)
  : MovableEntity(scope, id, isEnabled, x, y, 0.2, 0.2) {
  this->setTexture(texturePath);
  this->registerBindings();
}

void Entities::PlayerShip::registerBindings()
{
  std::function<void(void)> f = std::bind(&PlayerShip::moveUp, this);
  this->registerCallback(sf::Keyboard::Z, f);
  std::function<void(void)> f1 = std::bind(&PlayerShip::moveDown, this);
  this->registerCallback(sf::Keyboard::S, f1);
  std::function<void(void)> f2 = std::bind(&PlayerShip::moveLeft, this);
  this->registerCallback(sf::Keyboard::Q, f2);
  std::function<void(void)> f3 = std::bind(&PlayerShip::moveRight, this);
  this->registerCallback(sf::Keyboard::D, f3);
}

void Entities::PlayerShip::update() {
}

