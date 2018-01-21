/*
** Server.cpp for r-type in /home/god/TEK3/C++/R-type/sources/server/sources/Server.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Wed Jan 10 16:45:03 2018 Maxime PILLON
** Last update Wed Jan 10 16:45:05 2018 Maxime PILLON
*/


#include <functional>
#include "server/Server.hpp"
#include "server/Protocol.hpp"
#include "logger/Logger.hpp"

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
                {network::protocol::HeaderType::Error, 0};
        if (client->Recv(&header, sizeof(header), MSG_WAITALL) <= 0)
            return;
        if (header.type == network::protocol::HeaderType::Connect) {
            commandConnect(client);
        } else if (header.type == network::protocol::HeaderType::List) {
            commandList(client);
        }
    }
}

void server::Server::commandConnect(std::unique_ptr<mysocket::Socket>& client) {
    network::protocol::ConnexionResponse res = {network::protocol::Status::Error, network::protocol::PlayerColor::Error, 0};
    network::protocol::Connexion con{};

    std::memset(&con, 0, sizeof(con));

    if (client->Recv(&con, sizeof(con), 0) <= 0)
        return;
    if (_games.find(con.name) != _games.end()) {
        _games_m.lock();
        if (_games[con.name]->_passwd.length() > 0 && _games[con.name]->_passwd == con.pass) {
            if (_games[con.name]->nbPlayer >= 4) {
                res.status = network::protocol::Status::GameFull;
                sendTcpResponse(client, network::protocol::HeaderType::Connect, res);
            } else {
                res.color = static_cast<network::protocol::PlayerColor>(_games[con.name]->nbPlayer.load());
                res.status = network::protocol::Status::Ok;
                res.port = _games[con.name]->getPort();
                _games[con.name]->setIP(client->GetPeerRawAddress(), _games[con.name]->nbPlayer.load());
                sendTcpResponse(client, network::protocol::HeaderType::Connect, res);
                ++_games[con.name]->nbPlayer;
            }
        } else {
            sendTcpResponse(client, network::protocol::HeaderType::Connect, res);
        }
        _games_m.unlock();
    } else {
        try {
            _games_m.lock();
            _games[con.name] = std::make_shared<server::Game>(con.name, con.pass, _port);
            auto game = _games[con.name];
            _games_m.unlock();
            res.color = static_cast<network::protocol::PlayerColor>(game->nbPlayer.load());
            res.status = network::protocol::Status::Ok;
            res.port = game->getPort();
            _games[con.name]->setIP(client->GetPeerRawAddress(), _games[con.name]->nbPlayer.load());
            sendTcpResponse(client, network::protocol::HeaderType::Connect, res);
            ++game->nbPlayer;
            std::thread t(&Game::start, std::ref(*game));
            t.detach();
        }
        catch (mysocket::SocketException const& e) {
            // LOG
        }
        catch (...) {
            // LOG
        }
        ++_port;
    }
}

// TODO: This does not work !
void server::Server::commandList(std::unique_ptr<mysocket::Socket>& client) {
//    network::protocol::List con;
//
//    std::memset(&con, 0, sizeof(con));
//    network::protocol::ListResponse res;
//
//    if (client->Recv(con, sizeof(con), 0) <= 0)
//        return;
//    if (strlen(con.pattern) > 0) {
//
//    } else {
//        res.status = network::protocol::Status::STATUS_OK;
//        res.nelts = this->_games.size();
//        std::list<std::string> results;
//        for (auto it : _games)
//            results.push_back(it.first);
//        res.results = results;
//        sendTcpResponse(client, network::protocol::HeaderType::LIST, res);
//    }
}