#include <iostream>
#include "server/Game.hpp"
#include "server/Protocol.hpp"

namespace server {
    Game::Game(const char *name, unsigned short port)
        : _port(port), _socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP),
          _ips{0, 0, 0, 0}, _ips_mutex(), _name(name), _passwd(), nbPlayer(0) {
        _socket.setAddress(_port, "0.0.0.0");
        _socket.Bind();
    }

    Game::Game(const char *name, const char *passwd, unsigned short port)
        : _port(port), _socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP),
          _ips{0, 0, 0, 0}, _ips_mutex(), _name(name), _passwd(passwd), nbPlayer(0) {
        _socket.setAddress(_port, "0.0.0.0");
        _socket.Bind();
    }

    void Game::start() {
        bool end{false};

        while (!end) {
            mysocket::InetAddr addr{};
            mysocket::InetAddr send_addr{};
            char buf[1024];

            send_addr.SetPort(43000);
            std::memset(buf, 0, 1024);
            if (_socket.RecvFrom(buf, 1024, 0, addr) >= 0) {
                if (!checkIP(addr.GetStruct().sin_addr.s_addr))
                    continue;
                auto* hdr = reinterpret_cast<network::protocol::Header*>(buf);
//                auto* odr = reinterpret_cast<network::protocol::ObjectHeader*>(hdr + 1);
                _ips_mutex.lock();
                for (int i = 0; i < 4; ++i) {
                    if (_ips[i] == addr.GetStruct().sin_addr.s_addr)
                        continue;
                    send_addr.SetAddress(addr.GetStruct().sin_addr.s_addr);
                    _socket.SendTo(hdr, hdr->size + sizeof(network::protocol::Header), 0, send_addr);
                }
                _ips_mutex.unlock();
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