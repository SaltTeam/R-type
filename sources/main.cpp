
#include <iostream>

#include "network/Addr.hpp"
#include "engine/Runner.hpp"
#include "services/TestService.hpp"
#include "engine/service/NetService.hpp"
#include "engine/service/GameService.hpp"
#include "engine/service/GraphicalService.hpp"
#include "scopes/TestScope.hpp"

static void init() {
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

static void end() {
#ifdef WIN32
    WSACleanup();
#endif
}

int main() {
    init();

    auto e = ENGINE();

    e.addService<GAME_SERVICE>();
    e.findService<GAME_SERVICE>()->registerBaseScope<Scopes::TestScope>();
    e.addService<GRAPHICAL_SERVICE>();
    e.addService<NET_SERVICE>();

    e.run();

    end();
}
