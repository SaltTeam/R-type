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

        enum class Type : uint64_t {
            ASTEROID_BIG,
            ASTEROID_MED,
            ASTEROID_SMALL,
            ASTEROID_TINY,
            POWERUP_DAMAGE,
            POWERUP_HEAL,
            POWERUP_SHIELD,
            POWERUP_SPEED,
            LASER1,
            LASER2,
            LASER3,
            LASER4,
            BOSS_LEFTPART,
            BOSS_MIDDLEPART,
            BOSS_RIGHTPART,
            SHIP_WING,
            SHIP_ARC,
            SHIP_INTERCEPTOR,
            SHIP_TIEADVANCE,
            SHIP_TIEAVENGER,
            SHIP_TIEBOMBER,
            SHIP_TIEEXPERIMENT,
            SHIP_TIEFIGHTER,
            SHIP_XWING,
            SHIP_YWING
        };

        enum class Action {
            Update = 0,
            Delete = 1,
        };

        enum class Status : int {
            Ok = 200,
            Error = 500,
            PassError = 501,
            GameFull = 502
        };

        enum class HeaderType {
            Error = 0,
            Connect = 1,
            List = 2,
            Object = 3
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
            PlayerColor color;
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
        struct SBase {
            ObjectHeader header;
            bool isEnabled;
            float pos_x;
            float pos_y;
        };

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
        struct SMovable {
            struct SBase base;
            float speed_x;
            float speed_y;
        };
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
        struct SShip {
            struct SMovable base;
            short team;
            int health;
            int shield;
        };
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
        struct SProjectile {
            struct SMovable base;
            short team;
            int damage;
        };
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
        struct SPowerUp {
            struct SMovable base;
            short grade;
        };
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
