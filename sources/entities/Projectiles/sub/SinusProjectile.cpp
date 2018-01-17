//
// Created by delacr_a on 16/01/18.
//

#include "SinusProjectile.hpp"

void Entities::SinusProjectile::update() {
    Projectile::update();
    if (add)
        speed.x = 0.1;
    else
        speed.x = -0.1;
    if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - this->lastTurn).count() >=
            (first ? 250 : 500))
    {
        add = !add;
        first = false;
        this->lastTurn = std::chrono::system_clock::now();
    }
}
