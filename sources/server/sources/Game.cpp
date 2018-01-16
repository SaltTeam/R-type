#include "server/Game.hpp"

namespace server {
    Game::Game(const char* name, unsigned short port)
            : _name(name), _passwd(), _port(port), _socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) {
        _socket.setAddress(_port, "0.0.0.0");
        _socket.Bind();
    }

    Game::Game(const char* name, const char* passwd, unsigned short port)
            : _name(name), _passwd(passwd), _port(port), _socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP) {
        _socket.setAddress(_port, "0.0.0.0");
        _socket.Bind();
    }

    unsigned short Game::getPort() const {
        return _port;
    }

    void Game::start() {
        bool end {false};

        while (!end) {
            mysocket::InetAddr addr{};
            char buf[1024];

            std::memset(buf, 0, 1024);
            if (_socket.RecvFrom(buf, 1024, 0, addr) <= 0)
                continue;

        }
    }
}