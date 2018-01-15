
#pragma once

#include "engine/entity/MovableEntity.hpp"
#include "Weapon.hpp"

namespace Entities {
    class PlayerShip : public MOVABLE_ENTITY {
    protected:
	PlayerShip(SCOPE *scope, uint64_t id, const std::string &texturePath, bool isEnabled = true,
		   float const &x = 0, float const &y = 0, float const &xSpeed = 0.2, float const &ySpeed = 0.2);

	void update() override;

	void shoot();

	void registerBindings();

	Weapon weapon;
    };
}
