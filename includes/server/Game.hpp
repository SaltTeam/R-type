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
#include <mutex>
#include "network/Socket.hpp"

namespace server {

    class Game {
    protected:
        std::atomic_ushort _port;
        mysocket::Socket _socket;
        std::array<unsigned long, 4> _ips;
        std::mutex _ips_mutex;

    public:
        std::string _name;
        std::string _passwd;
        std::atomic_int nbPlayer;

    public:
        explicit Game(const char* name, unsigned short port);

        Game(const char* name, const char* passwd, unsigned short port);

    public:
        unsigned short getPort() const;
        void setIP(unsigned long addr, int idx);
        void unsetIP(int idx);
        unsigned long getIP(int idx);

    protected:
        bool checkIP(unsigned long addr);

    public:
        void start();
    };
}