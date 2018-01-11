//
// Created by delacr_a on 11/01/18.
//

#ifndef R_TYPE_MOVABLEENTITY_HPP
#define R_TYPE_MOVABLEENTITY_HPP

#pragma once

#include "engine/ForwardDeclaration.hpp"

namespace Engine {
  namespace Entities {

    class MovableEntity : public ENTITY {
    public:
      MovableEntity(SCOPE *scope, uint64_t id, bool isEnabled = true, float const &x = 0, float const &y = 0)
        :BaseEntity(scope, id, isEnabled, x, y) {};
      void moveUp();
      void moveDown();
      void moveRight();
      void moveLeft();
    };
  }
}

#endif //R_TYPE_MOVABLEENTITY_HPP
