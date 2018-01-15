//
// Created by delacr_a on 11/01/18.
//

#pragma once

#include <random>

#include "engine/ForwardDeclaration.hpp"
#include "engine/entity/Entity.hpp"
#include "engine/entity/MovableEntity.hpp"

namespace Entities {
  class Asteroid : public MOVABLE_ENTITY{
  public:
    Asteroid(SCOPE *scope, uint64_t id, const std::string &texturePath, bool isEnabled = true,
	     float const &x = 0, float const &y = 0);

  protected:
    void update() override;

  };
}
