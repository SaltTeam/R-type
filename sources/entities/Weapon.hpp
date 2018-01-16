//
// Created by delacr_a on 12/01/18.
//

#pragma once

#include <ctime>
#include "engine/ForwardDeclaration.hpp"

namespace Entities {
  class Weapon {
  public:
    Weapon(SCOPE *scope, float const &cd = 1, int const &damage = 10);

    void shoot(sf::Vector2f const &position);

    void shoot(std::vector<sf::Vector2f> const &positions);

  protected:
    SCOPE *scope;
    float cd;
    int damage;
    time_t lastUse;

  };
}