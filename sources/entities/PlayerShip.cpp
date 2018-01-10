//
// Created by sylva on 10/01/2018.
//

#include "PlayerShip.hpp"

Entities::PlayerShip::PlayerShip(uint64_t id, const std::string &texturePath, bool isEnabled)
        : BaseEntity(id, texturePath, isEnabled) {
    this->setTexture(texturePath);
}

void Entities::PlayerShip::update() {
    this->position.x++;
}
