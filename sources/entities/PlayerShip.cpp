//
// Created by sylva on 10/01/2018.
//

#include "engine/scope/Scope.hpp"
#include "engine/service/GameService.hpp"
#include "PlayerShip.hpp"

Entities::PlayerShip::PlayerShip(SCOPE *scope, uint64_t id, const std::string &texturePath, bool isEnabled,
                                 float const &x, float const &y, const float &xSpeed, const float &ySpeed,
                                 Weapon const &weapon, int const &health, int const &shield)
        : MovableEntity(scope, id, isEnabled, x, y, xSpeed, ySpeed),
          weapon(weapon), health(health), shield(shield) {
    this->setTexture(texturePath);
    this->registerBindings();
}

void Entities::PlayerShip::registerBindings() {
    std::function<void(void)> f = std::bind(&PlayerShip::moveUp, this);
    this->registerCallback(sf::Keyboard::Z, f);
    std::function<void(void)> f1 = std::bind(&PlayerShip::moveDown, this);
    this->registerCallback(sf::Keyboard::S, f1);
    std::function<void(void)> f2 = std::bind(&PlayerShip::moveLeft, this);
    this->registerCallback(sf::Keyboard::Q, f2);
    std::function<void(void)> f3 = std::bind(&PlayerShip::moveRight, this);
    this->registerCallback(sf::Keyboard::D, f3);
    std::function<void(void)> f4 = std::bind(&PlayerShip::shoot, this);
    this->registerCallback(sf::Keyboard::Space, f4);

    std::function<void(ENTITY *)> f5 = std::bind(&PlayerShip::onCollision, this, std::placeholders::_1);
    this->registerCollisionBox(this->texture->sprite.getGlobalBounds(), f5);
}

void Entities::PlayerShip::shoot() {
    this->weapon.shoot(this->canons, this->position);
}

void Entities::PlayerShip::update() {
    MOVABLE_ENTITY::update();
    if (this->health <= 0)
        this->scope->entityManager.remove(this);
}

void Entities::PlayerShip::onCollision(ENTITY *other) {
}

void Entities::PlayerShip::takeDamage(int const &value) {
    if (this->shield > value) {
        this->shield -= value;
    } else {
        this->health -= (value - this->shield);
        this->shield = 0;
    }
}
