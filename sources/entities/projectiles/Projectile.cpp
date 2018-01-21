//
// Created by delacr_a on 12/01/18.
//

#include "Projectile.hpp"
#include "entities/ships/PlayerShip.hpp"
#include "entities/asteroids/Asteroid.hpp"

Entities::Projectile::Projectile(SCOPE *scope, uint64_t id, network::protocol::PlayerColor playerColor, network::protocol::Update updateType,
                                 std::string const &texturePath, bool isEnabled,
                                 float const x, float const y, float const xSpeed, float const ySpeed,
                                 int const damage, Entities::Ship::TEAM originTeam, network::protocol::Type Type)
        : MovableEntity(scope, id, playerColor, updateType, 250,
                        isEnabled, x, y, xSpeed, ySpeed), damage(damage), originTeam(originTeam) {
    this->type = Type;
    this->setTexture(texturePath);
    this->position.x -= this->texture->sprite.getGlobalBounds().width / 2;
    std::function<void(ENTITY *)> f = std::bind(&Projectile::onCollision, this, std::placeholders::_1);
    this->registerCollisionBox(this->texture->sprite.getGlobalBounds(), f);
}

void Entities::Projectile::update() {
    this->move();
    MOVABLE_ENTITY::update();
}

void Entities::Projectile::onCollision(ENTITY *other) {
    if (!other->isEnabled)
        return;
    if (dynamic_cast<Entities::Asteroid *>(other) != nullptr) {
        this->scope->removeEntity(other);
        this->scope->removeEntity(this);
    } else if (dynamic_cast<Entities::Ship *>(other) != nullptr)
        if (dynamic_cast<Entities::Ship *>(other)->getTeam() != this->originTeam) {
            dynamic_cast<Entities::Ship *>(other)->takeDamage(this->damage);
            this->scope->removeEntity(this);
        }
}
