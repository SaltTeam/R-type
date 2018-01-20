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
            Error = -1,
            Blue = 0,
            Green,
            Red,
            Yellow
        };

        enum class Update {
            Master = 0,
            Instanciated,
            Replica
        };

        enum class Type : short {
            PROJECTILE,
            SHIP,
            ASTEROID,
            POWERUP
        };

        enum class Action {
            Update = 0,
            Delete = 1,
        };

        enum class Status {
            Ok = 200,
            Error = 500,
            PassError = 501,
            GameFull = 502
        };

        enum class HeaderType {
            Error = 0,
            Connect = 1,
            List = 2
        };

        extern "C" {


#ifdef WIN32
#define PACKED
#pragma pack(push,1)
#else
#define PACKED __attribute__((packed))
#endif
        struct ObjectHeader {
            Update update;
            Type type;
            uint16_t refresh;
            uint64_t id;
            Action action;
            std::size_t size;
        } PACKED;
#ifdef WIN32
#pragma pack(pop)
#undef PACKED
#else
#undef PACKED
#endif

        struct SBase {
            ObjectHeader header;
            bool isEnabled;
            float pos_x;
            float pos_y;
        };
        struct SMovable {
            struct SBase base;
            float speed_x;
            float speed_y;
        };
        struct SShip {
            struct SMovable base;
            short team;
            int health;
            int shield;
        };
        struct SProjectile {
            struct SMovable base;
            short team;
            int damage;
        };
        struct SPowerUp {
            struct SMovable base;
            short grade;
        };


#ifdef WIN32
        #define PACKED
#pragma pack(push,1)
#else
#define PACKED __attribute__((packed))
#endif
        struct Header {
            HeaderType type;
            uint64_t size;
        } PACKED;
#ifdef WIN32
        #pragma pack(pop)
#undef PACKED
#else
#undef PACKED
#endif


#ifdef WIN32
        #define PACKED
#pragma pack(push,1)
#else
#define PACKED __attribute__((packed))
#endif
        struct Connexion {
            char name[256];
            char pass[256];
        } PACKED;
#ifdef WIN32
        #pragma pack(pop)
#undef PACKED
#else
#undef PACKED
#endif

#ifdef WIN32
        #define PACKED
#pragma pack(push,1)
#else
#define PACKED __attribute__((packed))
#endif
        struct List {
            char pattern[256];
        } PACKED;
#ifdef WIN32
        #pragma pack(pop)
#undef PACKED
#else
#undef PACKED
#endif

#ifdef WIN32
        #define PACKED
#pragma pack(push,1)
#else
#define PACKED __attribute__((packed))
#endif
        struct ConnexionResponse {
            Status status;
            PlayerColor color;
            unsigned short port;
        } PACKED;
#ifdef WIN32
        #pragma pack(pop)
#undef PACKED
#else
#undef PACKED
#endif
        
// TODO: This does not work !
//#ifdef WIN32
//        #define PACKED
//#pragma pack(push,1)
//#else
//#define PACKED __attribute__((packed))
//#endif
//        struct ListResponse {
//            Status status;
//            uint64_t nelts;
//            uint64_t selts;
//            std::list<std::string> results;
//        } PACKED;
//#ifdef WIN32
//        #pragma pack(pop)
//#undef PACKED
//#else
//#undef PACKED
//#endif


        }
    }
}
