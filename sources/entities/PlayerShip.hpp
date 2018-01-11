
#pragma once

#include "engine/entity/MovableEntity.hpp"

namespace Entities {
  class PlayerShip : public MOVABLE_ENTITY {
  public:
    PlayerShip(SCOPE *scope, uint64_t id, const std::string &texturePath, bool isEnabled = true,
	       float const &x = 0, float const &y = 0);

  protected:
    void update() override;

    void registerBindings();
  };
}
