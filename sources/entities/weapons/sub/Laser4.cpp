//
// Created by delacr_a on 16/01/18.
//

#include "entities/Projectiles/sub/SinusProjectile.hpp"
#include "Laser4.hpp"


void Entities::Laser4::shoot(std::vector<sf::Vector2f> const &canons, sf::Vector2f const &position) {
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - this->lastUse).count() >=
            (this->cd * 1000)) {
        for (auto &it : canons)
            this->spawnLasers(it + position);
        this->lastUse = std::chrono::system_clock::now();
    }
}

void Entities::Laser4::spawnLasers(sf::Vector2f const &position) {
    this->scope->entityManager.add<Entities::SinusProjectile>(LAYER::Layer1, this->scope, 2,
                                                              this->projectilePath, true,
                                                              position.x, position.y,
                                                              this->xSpeed, this->ySpeed, this->damage, this->originId);
}
