//
// Created by delacr_a on 17/01/18.
//

#include "Ship.hpp"

Entities::Ship::Ship(SCOPE *scope, uint64_t id, const std::string &texturePath, bool isEnabled,
                     Entities::Ship::TEAM team, float const &x, float const &y, float const &xSpeed,
                     float const &ySpeed, int const &health, const int &shield)
        : MovableEntity(scope, id, isEnabled, x, y, xSpeed, ySpeed),
          health(health), maxHealth(health), shield(shield), team(team) {
    this->setTexture(texturePath);
    std::function<void(ENTITY *)> f5 = std::bind(&Ship::onCollision, this, std::placeholders::_1);
    this->registerCollisionBox(this->texture->sprite.getGlobalBounds(), f5);
}

void Entities::Ship::shoot() {
    this->weapon->shoot(this->canons, this->position);
}

void Entities::Ship::update() {
    MOVABLE_ENTITY::update();
    if (this->health <= 0)
        this->scope->removeEntity(this);
}

void Entities::Ship::onCollision(ENTITY *other) {

}

void Entities::Ship::takeDamage(int value) {
    if (this->shield > value) {
        this->shield -= value;
    } else {
        this->health -= (value - this->shield);
        this->shield = 0;
    }
}

void Entities::Ship::gainHealth(GRADE grade) {
    std::cout << "Health gained" << std::endl;
    switch (grade)
    {
        case BRONZE:
            health += 30;
            break;
        case SILVER:
            health += 60;
            break;
        case GOLD:
            health += 90;
            break;
    }
    if (health > maxHealth)
        health = maxHealth;
}

void Entities::Ship::gainShield(GRADE grade) {
    switch (grade)
    {
        case BRONZE:
            shield += 30;
            break;
        case SILVER:
            shield += 60;
            break;
        case GOLD:
            shield += 90;
            break;
    }
}

void Entities::Ship::gainSpeed(GRADE grade) {
    switch (grade)
    {
        case BRONZE:
            speed.x *= 1.1;
            speed.y *= 1.1;
            break;
        case SILVER:
            speed.x *= 1.2;
            speed.y *= 1.2;
            break;
        case GOLD:
            speed.x *= 1.3;
            speed.y *= 1.3;
            break;
    }
}

void Entities::Ship::upgradeWeapon(GRADE grade) {
    this->weapon;
}

Entities::Ship::TEAM Entities::Ship::getTeam() {
    return this->team;
}

void Entities::Ship::moveUp() {
    if (this->position.y - this->speed.y > 0)
        MovableEntity::moveUp();
}

void Entities::Ship::moveDown() {
    if (this->position.y + this->speed.y + this->texture->sprite.getGlobalBounds().height <
        this->scope->gameService->getWindowSize().y)
        MovableEntity::moveDown();
}

void Entities::Ship::moveRight() {
    if (this->position.x + this->speed.x + this->texture->sprite.getGlobalBounds().width <
        this->scope->gameService->getWindowSize().x)
        MovableEntity::moveRight();
}

void Entities::Ship::moveLeft() {
    if (this->position.x - this->speed.x > 0)
        MovableEntity::moveLeft();
}
