#include <iostream>
#include "server/Game.hpp"

namespace server {
    Game::Game(const char *name, unsigned short port)
        : _port(port), _socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP),
          _ips{0, 0, 0, 0}, _ips_mutex(), _name(name), _passwd(), nbPlayer(0) {
        _socket.setAddress(_port, "0.0.0.0");
        _socket.Bind();
        _ips_mutex.unlock();
    }

    Game::Game(const char *name, const char *passwd, unsigned short port)
        : _port(port), _socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP),
          _ips{0, 0, 0, 0}, _ips_mutex(), _name(name), _passwd(passwd), nbPlayer(0) {
        _socket.setAddress(_port, "0.0.0.0");
        _socket.Bind();
        _ips_mutex.unlock();
    }

    void Game::start() {
        bool end{false};

        while (!end) {
            mysocket::InetAddr addr{};
            char buf[1024];

            std::memset(buf, 0, 1024);
            if (_socket.RecvFrom(buf, 1024, 0, addr) >= 0) {
                if (!checkIP(addr.GetStruct().sin_addr.s_addr))
                    continue;
                std::cout << "client send me: " << buf << std::endl;
                std::cout << "client port: " << ntohs(addr.GetStruct().sin_port) << std::endl;
                addr.SetPort(43000);
                _socket.SendTo("hello", 5, 0, addr);
            }

        }
    }

    void Game::setIP(unsigned long addr, int idx) {
        _ips_mutex.lock();
        _ips[idx] = addr;
        _ips_mutex.unlock();
    }

    void Game::unsetIP(int idx) {
        _ips_mutex.lock();
        _ips[idx] = 0;
        _ips_mutex.unlock();
    }

    unsigned long Game::getIP(int idx) {
        unsigned long ret = 0;
        _ips_mutex.lock();
        ret = _ips[idx];
        _ips_mutex.unlock();
        return ret;
    }

    unsigned short Game::getPort() const {
        return _port;
    }

    bool Game::checkIP(unsigned long addr) {
        for (int i = 0; i < 4; ++i) {
            if (getIP(i) == addr)
                return true;
        }
        return false;
    }

}