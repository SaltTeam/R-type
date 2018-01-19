/*
** main.cpp for r-type in /home/god/TEK3/C++/R-type/sources/server/main.cpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Wed Jan 10 15:50:24 2018 Maxime PILLON
** Last update Wed Jan 10 15:50:24 2018 Maxime PILLON
*/


#include <iostream>

#include "server/Server.hpp"
#include "engine/Runner.hpp"
#include "services/TestService.hpp"
#include "engine/service/NetService.hpp"

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

    try {
        server::Server server;
        server.start();
    } catch (std::exception& exception) {
        std::cout << exception.what();
    }
    end();
}
