/*
** Server.hpp for r-type in /home/god/TEK3/C++/R-type/sources/server/includes/Server.hpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Wed Jan 10 16:44:18 2018 Maxime PILLON
** Last update Wed Jan 10 16:44:18 2018 Maxime PILLON
*/

#pragma once

#include <list>
#include "Game.hpp"
#include "Protocol.hpp"

namespace server {

  class Server {
  protected:
    std::list<server::Game> _games;

  public:
    Server() = default;

    void start();
  };
}
