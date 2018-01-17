//
// Created by delacr_a on 17/01/18.
//

#include "Ship.hpp"

Entities::Ship::Ship(SCOPE *scope, uint64_t id, const std::string &texturePath, bool isEnabled,
                     Entities::Ship::TEAM team, float const &x, float const &y, float const &xSpeed,
                     float const &ySpeed, int const &health, const int &shield)
        : MovableEntity(scope, id, isEnabled, x, y, xSpeed, ySpeed),
          health(health), shield(shield), team(team) {
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

void Entities::Ship::takeDamage(int const &value) {
    if (this->shield > value) {
        this->shield -= value;
    } else {
        this->health -= (value - this->shield);
        this->shield = 0;
    }
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
