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
#include <atomic>
#include "network/Socket.hpp"

namespace server {

    class Game {
    protected:
        std::atomic_ushort _port;
        mysocket::Socket _socket;

    public:
        std::string _name;
        std::string _passwd;
        std::atomic_int nbPlayer = 0;

    public:
        explicit Game(const char* name, unsigned short port);

        Game(const char* name, const char* passwd, unsigned short port);

    public:
        unsigned short getPort() const;

    public:
        void start();
    };
}