/*
** Protocol.hpp for r-type in /home/god/TEK3/C++/R-type/sources/server/includes/Protocol.hpp
**
** Made by Maxime PILLON
** Login   <maxime.pillon@epitech.eu>
**
** Started on  Wed Jan 10 16:18:38 2018 Maxime PILLON
** Last update Wed Jan 10 16:18:38 2018 Maxime PILLON
*/

#pragma once

#include <string>
#include <list>

namespace network {
    namespace protocol {
        enum class PlayerColor {
            ERROR = -1,
            BLUE = 0,
            GREEN,
            RED,
            YELLOW
        };

        enum class Update {
            MASTER = 0,
            INSTANCIATED,
            REPLICA
        };

        enum class Type {
        };

        enum class Action {
            UPDATE = 0,
            DELETE = 1,
        };

        enum class Status {
            STATUS_OK = 200,
            STATUS_ERROR = 500,
	    STATUS_PASSERROR = 501,
	    STATUS_FULL = 502
        };

        enum class HeaderType {
            ERROR = 0,
            CONNECT = 1,
            LIST = 2
        };

        extern "C" {
        struct Header {
            HeaderType type;
            uint64_t size;
        } __attribute__((packed));

        struct Connexion {
            const char name[256];
            const char pass[256];
        } __attribute__((packed));

        struct List {
            const char pattern[256];
        } __attribute__((packed));

        struct ConnexionResponse {
            Status status;
            PlayerColor color;
            unsigned short port;
        };

        // TODO: This does not work !
        struct ListResponse {
            Status status;
            uint64_t nelts;
            uint64_t selts;
            std::list<std::string> results;
        } __attribute__((packed));

        struct ObjectHeader {
            Update update;
            Type type;
            uint16_t refresh;
            uint64_t id;
            Action action;
        } __attribute__((packed));

        }
    }
}
