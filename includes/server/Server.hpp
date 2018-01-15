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

#include <map>
#include "Game.hpp"
#include "Protocol.hpp"
#include "network/Socket.hpp"
#include "network/Select.hpp"

namespace server {

    class Server {
    protected:
        std::map<std::string, server::Game> _games;
        mysocket::Socket _socket;
        mysocket::Select _select;

    public:
        Server();

        void start();

    protected:
        void setSelect();
        void handleConnection();
        void commandConnect(std::unique_ptr<mysocket::Socket>& client);
        void commandList(std::unique_ptr<mysocket::Socket>& client);
    };
}
