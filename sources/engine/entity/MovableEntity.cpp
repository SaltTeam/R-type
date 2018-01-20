//
// Created by delacr_a on 11/01/18.
//

#include "engine/scope/Scope.hpp"
#include "MovableEntity.hpp"
#include "engine/service/GameService.hpp"

//<editor-fold> MOVE FUNCTIONS

#define MOVE_MULTIPLIER 1000

void MOVABLE_ENTITY::moveUp() {
    this->position.y -= this->speed.y * (GRAPHICAL_SERVICE::deltaTime.asSeconds() * MOVE_MULTIPLIER);
}

void MOVABLE_ENTITY::moveDown() {
    this->position.y += this->speed.y * (GRAPHICAL_SERVICE::deltaTime.asSeconds() * MOVE_MULTIPLIER);
}

void MOVABLE_ENTITY::moveLeft() {
    this->position.x -= this->speed.x * (GRAPHICAL_SERVICE::deltaTime.asSeconds() * MOVE_MULTIPLIER);
}

void MOVABLE_ENTITY::moveRight() {
    this->position.x += this->speed.x * (GRAPHICAL_SERVICE::deltaTime.asSeconds() * MOVE_MULTIPLIER);
}

void MOVABLE_ENTITY::move() {
    this->position.x += this->speed.x * (GRAPHICAL_SERVICE::deltaTime.asSeconds() * MOVE_MULTIPLIER);
    this->position.y += this->speed.y * (GRAPHICAL_SERVICE::deltaTime.asSeconds() * MOVE_MULTIPLIER);
}

#undef MOVE_MULTIPLIER

//</editor-fold>



//<editor-fold> SETTERS

void MOVABLE_ENTITY::setSpeed(sf::Vector2f const &speed) {
    this->speed = speed;
}

void MOVABLE_ENTITY::setSpeed(float const &xy_speed) {
    this->speed = {xy_speed, xy_speed};
}

void MOVABLE_ENTITY::setSpeed(float const &x_speed, float const &y_speed) {
    this->speed = {x_speed, y_speed};
}

void MOVABLE_ENTITY::update() {
    this->scope->collisionManager.checkCollision(this);
    sf::Vector2u borders = this->scope->gameService->getWindowSize();
    sf::FloatRect sides = this->texture->sprite.getGlobalBounds();
    if (this->position.x + sides.width < 0 || this->position.x > borders.x)
        this->scope->removeEntity(this);
    else if (this->position.y + sides.height < 0 || this->position.y > borders.y)
        this->scope->removeEntity(this);
}
//</editor-fold>
