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
#include <memory>
#include <thread>
#include <mutex>
#include "Game.hpp"
#include "Protocol.hpp"
#include "network/Socket.hpp"
#include "network/Select.hpp"

namespace server {

    class Server {
    protected:
        std::map<std::string, std::shared_ptr<server::Game>> _games;
        mysocket::Socket _socket;
        mysocket::Select _select;
        unsigned short _port = 42001;
        std::mutex _games_m;

    public:
        Server();

        void start();

    protected:
        void setSelect();
        void handleConnection();
        void commandConnect(std::unique_ptr<mysocket::Socket>& client);
        void commandList(std::unique_ptr<mysocket::Socket>& client);

        template <class T>
        void sendTcpResponse(std::unique_ptr<mysocket::Socket>& client, network::protocol::HeaderType type, T const& obj);
    };

    template <class T>
    void Server::sendTcpResponse(std::unique_ptr<mysocket::Socket>& client,
                                 network::protocol::HeaderType type,
                                 T const& obj) {
        std::basic_string<unsigned char> msg;
        network::protocol::Header header = {type, sizeof(T)};

        msg.append(reinterpret_cast<const unsigned char*>(&header), sizeof(network::protocol::Header));
        msg.append(reinterpret_cast<const unsigned char*>(&obj), sizeof(T));
        client->Send(msg.data(), msg.length(), 0);
    }
}
