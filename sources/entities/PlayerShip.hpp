
#pragma once

#include "engine/entity/MovableEntity.hpp"
#include "Weapon.hpp"

namespace Entities {
    class PlayerShip : public MOVABLE_ENTITY {
    protected:
	PlayerShip(SCOPE *scope, uint64_t id, const std::string &texturePath, bool isEnabled,
		   float const &x, float const &y, float const &xSpeed, float const &ySpeed,
		   Weapon const &weapon);

	void update() override;

	void shoot();

	void registerBindings();

	void onCollision(ENTITY *other);

	Weapon weapon;

	std::vector<sf::Vector2f> canons;

	int health;

	int shield;
    };
}
