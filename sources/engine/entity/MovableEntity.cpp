//
// Created by delacr_a on 11/01/18.
//

#include <engine/scope/Scope.hpp>
#include <iostream>
#include "Entity.hpp"
#include "MovableEntity.hpp"

//<editor-fold> MOVE FUNCTIONS

void MOVABLE_ENTITY::moveUp() {
    this->position.y -= this->speed.y;
}

void MOVABLE_ENTITY::moveDown() {
    this->position.y += this->speed.y;
}

void MOVABLE_ENTITY::moveLeft() {
    this->position.x -= this->speed.x;
}

void MOVABLE_ENTITY::moveRight() {
    this->position.x += this->speed.x;
}

void MOVABLE_ENTITY::move() {
    this->position.x += this->speed.x;
    this->position.y += this->speed.y;
}
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
}
//</editor-fold>
