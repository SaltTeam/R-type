//
// Created by delacr_a on 17/01/18.
//

#include "entities/asteroids/Asteroid.hpp"
#include "entities/ships/Ship.hpp"
#include "APowerUp.hpp"

Entities::APowerUp::APowerUp(SCOPE *scope, uint64_t id, bool isEnabled, float const &x,
                             float const &y, float const &xSpeed, float const &ySpeed, GRADE grade)
        : MovableEntity(scope, id, network::protocol::Update::Instanciated, 250, isEnabled, x, y, xSpeed, ySpeed),
          grade(grade) {}

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

void Entities::APowerUp::registerTexture(std::string const &path) {
    this->setTexture(path);
    this->position.x -= this->texture->sprite.getGlobalBounds().width / 2;
    std::function<void(ENTITY *)> f = std::bind(&APowerUp::onCollision, this, std::placeholders::_1);
    this->registerCollisionBox(this->texture->sprite.getGlobalBounds(), f);
}

std::string Entities::APowerUp::getEnumName(GRADE grade) {
    switch (grade)
    {
        case BRONZE:
            return "bronze";
        case SILVER:
            return "silver";
        case GOLD:
            return "gold";
    }
}
