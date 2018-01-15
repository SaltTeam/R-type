//
// Created by sylva on 10/01/2018.
//

#include <iostream>
#include "engine/scope/Scope.hpp"
#include "engine/service/GameService.hpp"
#include "PlayerShip.hpp"

Entities::PlayerShip::PlayerShip(SCOPE *scope, uint64_t id, const std::string &texturePath, bool isEnabled,
                                 float const &x, float const &y)
        : MovableEntity(scope, id, isEnabled, x, y, 0.2, 0.2), weapon(scope, 0.5) {
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
    this->registerCollisionBox(this->texture->sprite.getScale(), f5);
}

void Entities::PlayerShip::shoot() {
    std::vector<sf::Vector2f> vec = std::vector<sf::Vector2f>();
    vec.push_back(this->position);
    vec.push_back(sf::Vector2f(this->position.x + 150, this->position.y));
    this->weapon.shoot(vec);
}

void Entities::PlayerShip::update() {
    MOVABLE_ENTITY::update();
}

void Entities::PlayerShip::onCollision(ENTITY *other) {
    std::cout << "PlayerShip collision" << std::endl;
}
