//
// Created by delacr_a on 11/01/18.
//

#pragma once

#include "engine/ForwardDeclaration.hpp"

namespace Engine {
  namespace Entities {

    class MovableEntity : public ENTITY {
    protected:
      sf::Vector2f speed;

    public:

      MovableEntity(SCOPE *scope, uint64_t id, bool isEnabled = true,
		    float const &x = 0, float const &y = 0,
		    float const &x_speed = 0, float const &y_speed = 0)
	: BaseEntity(scope, id, isEnabled, x, y), speed{x_speed, y_speed} {};

      void moveUp();

      void moveDown();

      void moveRight();

      void moveLeft();

      void move();

      void setSpeed(sf::Vector2f const &speed);
      void setSpeed(float const &x_speed, float const &y_speed);
      void setSpeed(float const &xy_speed);
    };
  }
}
