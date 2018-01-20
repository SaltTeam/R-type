//
// Created by delacr_a on 17/01/18.
//

#include "entities/asteroids/Asteroid.hpp"
#include "entities/ships/Ship.hpp"
#include "APowerUp.hpp"

Entities::APowerUp::APowerUp(SCOPE *scope, uint64_t id, bool isEnabled, float const &x,
                             float const &y, float const &xSpeed, float const &ySpeed, GRADE grade)
        : MovableEntity(scope, id, isEnabled, x, y, xSpeed, ySpeed), grade(grade) {
    type = network::protocol::Type::POWERUP;
}

void Entities::APowerUp::update() {
    this->move();
    MOVABLE_ENTITY::update();
}

void Entities::APowerUp::onCollision(ENTITY *other) {
    if (!other->isEnabled)
        return;
    else if (dynamic_cast<Entities::PlayerShip *>(other) != nullptr) {
        this->interract(dynamic_cast<Entities::PlayerShip *>(other));
        this->scope->removeEntity(this);
    }
}
