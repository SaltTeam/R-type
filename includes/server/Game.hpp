/*
** Game.hpp for r-type in /home/god/TEK3/C++/R-type/sources/server/includes/Game.hpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Wed Jan 10 16:04:47 2018 Maxime PILLON
** Last update Wed Jan 10 16:04:47 2018 Maxime PILLON
*/

#pragma once

#include <string>

namespace server {

    class Game {
    protected:

    public:
	Game(const char *name, const char *password) : _name(name), _passwd(password) {}

	const char *_name;
	const char *_passwd;
	int nbPlayer = 0;

    public:
	explicit Game(const char *name) : _name(name), _passwd() {}

	explicit Game(const char *name, const char *passwd) : _name(name),
								_passwd(
								    passwd) {}
    };
}