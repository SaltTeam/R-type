//
// Created by sylva on 10/01/2018.
//

#include "entities/Asteroid.hpp"
#include "engine/scope/Scope.hpp"
#include "engine/service/GameService.hpp"
#include "PlayerShip.hpp"

Entities::PlayerShip::PlayerShip(SCOPE *scope, uint64_t id, const std::string &texturePath, bool isEnabled,
                                 float const &x, float const &y, const float &xSpeed, const float &ySpeed,
                                 int const &health, int const &shield)
        : Ship(scope, id, texturePath, isEnabled, Entities::Ship::PLAYER, x, y, xSpeed, ySpeed, health, shield) {
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
}

void Entities::PlayerShip::onCollision(ENTITY *other) {
    if (!other->isEnabled)
        return;
    if (dynamic_cast<Entities::Asteroid *>(other) != nullptr)
        if (this->shield == 0)
            this->scope->removeEntity(this);
        else
            this->shield = 0;
    else if (dynamic_cast<Entities::Ship *>(other) != nullptr)
        if (dynamic_cast<Entities::Ship *>(other)->getTeam() != this->team) {
            if (dynamic_cast<Entities::Ship *>(other)->getShield() == 0)
                this->scope->removeEntity(other);
            if (this->shield == 0)
                this->scope->removeEntity(this);
            else
                this->shield = 0;
        }

}
