
#include <iostream>
#include <iomanip>

#include "engine/Runner.hpp"
#include "services/TestService.hpp"
#include "engine/service/NetService.hpp"
#include "engine/service/GameService.hpp"
#include "engine/service/GraphicalService.hpp"
#include "scopes/TestScope.hpp"
#include "network/Socket.hpp"
#include "server/Protocol.hpp"

static void init()
{
#ifdef WIN32
    WSADATA wsa;
    int err = WSAStartup(MAKEWORD(2, 2), &wsa);
    if(err < 0)
    {
        puts("WSAStartup failed !");
        exit(EXIT_FAILURE);
    }
#endif
}

static void end()
{
#ifdef WIN32
    WSACleanup();
#endif
}

int main() {
    init();
    
    mysocket::Socket ud{AF_INET, SOCK_DGRAM, IPPROTO_UDP};
    mysocket::Socket tc{AF_INET, SOCK_STREAM, IPPROTO_TCP};
    network::protocol::Header hdr{};
    network::protocol::Connexion connect{};


    hdr.type = network::protocol::HeaderType::Connect;
    hdr.size = sizeof(network::protocol::Connexion);
    std::strncpy(connect.name, "zerzerzer", 256);
    std::strncpy(connect.pass, "titi", 256);

    tc.setAddress(42000, "127.0.0.1");
    std::cout << "Connect return: " << tc.Connect() << std::endl;


    std::basic_string<unsigned char> msg;

    msg.append(reinterpret_cast<unsigned char*>(&hdr), sizeof(network::protocol::Header));
    msg.append(reinterpret_cast<unsigned char*>(&connect), hdr.size);
    tc.Send(msg.data(), msg.length(), 0);

    network::protocol::Header mdr{};
    network::protocol::ConnexionResponse resp{};
    tc.Recv(&mdr, sizeof(mdr));
    std::cout << "header type response: " << (int)mdr.type << std::endl;
    tc.Recv(&resp, sizeof(resp));
    std::cout << "color response: " << (int)resp.color << std::endl;
    std::cout << "status response: " << (int) resp.status << std::endl;
    std::cout << "port: " << resp.port << std::endl;

    ud.setAddress(43000, "0.0.0.0");
    ud.Bind();
    mysocket::InetAddr server("127.0.0.1", resp.port);
    ud.SendTo("coucou", 6, 0, server);

    mysocket::InetAddr addr{};
    char buf[1024];
    std::memset(buf, 0, 1024);
    ud.RecvFrom(buf, 1024, 0, addr);
    std::cout << "recv from server: " << buf << std::endl;

    end();
    return 0;
}
