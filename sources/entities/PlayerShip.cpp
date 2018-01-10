//
// Created by sylva on 10/01/2018.
//

#include "engine/scope/Scope.hpp"
#include "engine/service/GameService.hpp"
#include "PlayerShip.hpp"

Entities::PlayerShip::PlayerShip(SCOPE *scope, uint64_t id, const std::string &texturePath, bool isEnabled)
        : BaseEntity(scope, id, isEnabled) {
    this->setTexture(texturePath);
    this->registerCallback(sf::Keyboard::Z, std::bind(&PlayerShip::moveUp, this));
}

void Entities::PlayerShip::update() {
}

void Entities::PlayerShip::moveUp() {
    this->position.y--;
}
