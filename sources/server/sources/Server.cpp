/*
** Server.cpp for r-type in /home/god/TEK3/C++/R-type/sources/server/sources/Server.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Wed Jan 10 16:45:03 2018 Maxime PILLON
** Last update Wed Jan 10 16:45:05 2018 Maxime PILLON
*/


#include "server/Server.hpp"
#include "server/Protocol.hpp"

server::Server::Server()
        : _games(), _socket(AF_INET, SOCK_STREAM, IPPROTO_TCP), _select() {
    _socket.setAddress(42000, "0.0.0.0");
    _socket.Bind();
    _socket.Listen(42);
}

void server::Server::start() {
    for (;;) {
        setSelect();
        _select.wait();
        handleConnection();
    }
}

void server::Server::setSelect() {
    _select.clearExceptFd();
    _select.clearReadFd();
    _select.clearWriteFd();
    _select.addReadFd(_socket.getSocketFd());
}

void server::Server::handleConnection() {
    if (_select.isFdSetRead(_socket.getSocketFd())) {
        std::unique_ptr<mysocket::Socket> client(_socket.Accept());
        if (client == nullptr)
            return;
        network::protocol::Header header =
                {network::protocol::HeaderType::ERROR, 0};
        if (client->Recv(header, sizeof(header), 0) <= 0)
            return;
        if (header.type == network::protocol::HeaderType::CONNECT) {
            commandConnect(client);
        }
        else if (header.type == network::protocol::HeaderType::LIST) {
            commandList(client);
        }
    }
}

void server::Server::commandConnect(std::unique_ptr<mysocket::Socket>& client) {
    network::protocol::Connexion con;

    std::memset(&con, 0, sizeof(con));
    if (client->Recv(con, sizeof(con), 0) <= 0)
        return;
    if (_games.find(con.name) != _games.end()) {
        if (_games[con.name]._passwd.length() > 0 && _games[con.name]._passwd == con.pass) {
            // Add the player to the game and send response back
            network::protocol::ConnexionResponse res;
        }
        else {
            network::protocol::ConnexionResponse res;

            res.color = network::protocol::PlayerColor::ERROR;
            res.status = network::protocol::Status::STATUS_ERROR;
            client->Send(res, sizeof(res), 0);
        }
    }
    else {
        // Create a new game
        // Add the player to the game and send response back
        network::protocol::ConnexionResponse res;
    }
}