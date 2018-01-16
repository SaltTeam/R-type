
#include <iostream>
#include <engine/scope/Scope.hpp>
#include "Asteroid.hpp"

Entities::Asteroid::Asteroid(SCOPE *scope, uint64_t id, const std::string &texturePath, bool isEnabled,
                             const float &x, const float &y)
        : MovableEntity(scope, id, isEnabled, x, y) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(-0.2, 0.2);

    this->setTexture(texturePath);
    this->setSpeed(dist(mt), dist(mt));
    this->setPosition(400, 400);

    std::function<void(ENTITY *)> f = std::bind(&Asteroid::onCollision, this, std::placeholders::_1);
    this->registerCollisionBox(this->texture->sprite.getScale(), f);
}

void Entities::Asteroid::update() {
    MOVABLE_ENTITY::update();
    this->move();
}

void Entities::Asteroid::onCollision(ENTITY *other) {
    this->scope->entityManager.remove(this);
}
