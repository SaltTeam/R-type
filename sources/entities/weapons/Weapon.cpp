//
// Created by delacr_a on 12/01/18.
//

#include <ctime>
#include <engine/scope/Scope.hpp>
#include <chrono>
#include "Weapon.hpp"
#include "entities/Projectiles/Projectile.hpp"
#include "entities/Asteroid.hpp"

void Entities::Weapon::shoot(std::vector<sf::Vector2f> const &canons, sf::Vector2f const &position) {
    if (std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - this->lastUse).count() >=
        (this->cd * 1000)) {
        for (auto &it : canons)
            this->spawnLasers(it + position);
        this->lastUse = std::chrono::system_clock::now();
    }
}

void Entities::Weapon::spawnLasers(sf::Vector2f const &position) {
    this->scope->entityManager.add<Entities::Projectile>(LAYER::Layer1, this->scope, 2,
                                                         this->projectilePath, true,
                                                         position.x, position.y,
                                                         this->xSpeed, this->ySpeed, this->damage, this->originId);
}