//
// Created by delacr_a on 12/01/18.
//

#include <iostream>
#include "Projectile.hpp"
#include "PlayerShip.hpp"
#include "Asteroid.hpp"

Entities::Projectile::Projectile(SCOPE *scope, uint64_t id, const std::string &texturePath, bool isEnabled,
				 float const &x, float const &y, float const &xSpeed, float const &ySpeed,
				 int const &damage, uint64_t const &originId)
    : MovableEntity(scope, id, isEnabled, x, y, xSpeed, ySpeed), damage(damage), originId(originId) {
    this->setTexture(texturePath);
    std::function<void(ENTITY *)> f = std::bind(&Projectile::onCollision, this, std::placeholders::_1);
    this->registerCollisionBox(this->texture->sprite.getGlobalBounds(), f);
}

void Entities::Projectile::update() {
    this->move();
    MOVABLE_ENTITY::update();
}

void Entities::Projectile::onCollision(ENTITY *other) {
    if (dynamic_cast<Entities::Asteroid*>(other) != nullptr)
    	this->scope->entityManager.remove(this);
    else if (dynamic_cast<Entities::PlayerShip*>(other) != nullptr)
	if (other->id != this->originId)
	{
	    std::cout << this->originId << " hit " << other->id << std::endl;
	    this->scope->entityManager.remove(this);
	}
}
