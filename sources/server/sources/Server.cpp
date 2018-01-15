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
    network::protocol::ConnexionResponse res;

    if (client->Recv(con, sizeof(con), 0) <= 0)
        return;
    if (_games.find(con.name) != _games.end()) {
        if (strlen(_games[con.name]._passwd) > 0 && _games[con.name]._passwd == con.pass) {
	    if (_games[con.name].nbPlayer == 4) {
		res.color = network::protocol::PlayerColor::ERROR;
		res.status = network::protocol::Status::STATUS_FULL;
		client->Send(res, sizeof(res), 0);
	    } else {
		res.color = static_cast<network::protocol::PlayerColor>(_games[con.name].nbPlayer);
		res.status = network::protocol::Status::STATUS_OK;
		client->Send(res, sizeof(res), 0);
		++_games[con.name].nbPlayer;
	    }
        } else {
            res.color = network::protocol::PlayerColor::ERROR;
            res.status = network::protocol::Status::STATUS_PASSERROR;
            client->Send(res, sizeof(res), 0);
        }
    }
    else {
	server::Game game(con.name, con.pass);
	this->_games.emplace(std::make_pair(con.name, game));
	res.color = static_cast<network::protocol::PlayerColor>(game.nbPlayer);
	res.status = network::protocol::Status::STATUS_OK;
	client->Send(res, sizeof(res), 0);
	++game.nbPlayer;
	// need to set a data socket for udp protocol.
    }
}

void server::Server::commandList(std::unique_ptr<mysocket::Socket> &client) {
    network::protocol::List con;

    std::memset(&con, 0, sizeof(con));
    network::protocol::ListResponse res;

    if (client->Recv(con, sizeof(con), 0) <= 0)
	return;
    if (strlen(con.pattern) > 0)
    {
	
    } else {
	res.status = network::protocol::Status::STATUS_OK;
	res.nelts = this->_games.size();
	std::list<std::string> results;
	for (auto it : _games)
	    results.push_back(it.first);
	res.results = results;
	client->Send(res, sizeof(res), 0);
    }
}