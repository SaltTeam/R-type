//
// Created by delacr_a on 11/01/18.
//

#include "Entity.hpp"
#include "MovableEntity.hpp"

void MOVABLE_ENTITY::moveUp() {
  this->position.y -= 0.2;
}

void MOVABLE_ENTITY::moveDown() {
  this->position.y += 0.2;
}

void MOVABLE_ENTITY::moveLeft() {
  this->position.x -= 0.2;
}

void MOVABLE_ENTITY::moveRight() {
  this->position.x  += 0.2;
}