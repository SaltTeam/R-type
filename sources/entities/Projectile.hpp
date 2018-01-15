//
// Created by delacr_a on 12/01/18.
//

#pragma once

#include "engine/ForwardDeclaration.hpp"
#include "engine/entity/Entity.hpp"
#include "engine/entity/MovableEntity.hpp"

namespace Entities {
  class Projectile : public MOVABLE_ENTITY {
  public:
    Projectile(SCOPE *scope, uint64_t id, const std::string &texturePath, bool isEnabled = true,
	       float const &x = 0, float const &y = 0);

    void update() override;
  };
}