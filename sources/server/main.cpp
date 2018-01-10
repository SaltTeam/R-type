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

#include "engine/Runner.hpp"
#include "services/TestService.hpp"
#include "engine/service/NetService.hpp"

int main() {
  Server server;

  try {
    server.start();
  } catch (std::exception &exception) {
    std::cout << exception.what();
  }
}
