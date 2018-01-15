/*
** Game.hpp for r-type in /home/god/TEK3/C++/R-type/sources/server/includes/Game.hpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Wed Jan 10 16:04:47 2018 Maxime PILLON
** Last update Wed Jan 10 16:04:47 2018 Maxime PILLON
*/

#pragma once

#include <string>

namespace server {

  class Game {
  protected:

  public:
    Game() = default;
    std::string& _name;
    std::string& _passwd;

  public:
    explicit Game(std::string& name) : _name(name), _passwd() {}
    explicit Game(std::string& name, std::string& passwd) : _name(name), _passwd(passwd) {}
  };
}