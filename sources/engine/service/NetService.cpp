
#include "entities/projectiles/Projectile.hpp"
#include "entities/powerups/APowerUp.hpp"
#include "NetService.hpp"
#include "engine/Runner.hpp"
#include "engine/entity/Entity.hpp"
#include "entities/ships/Ship.hpp"
#include "engine/scope/Scope.hpp"
#include "engine/service/GameService.hpp"
#include "entities/powerups/APowerUp.hpp"
#include "entities/projectiles/Projectile.hpp"
#include "entities/ships/Ship.hpp"

namespace Engine {
    network::protocol::PlayerColor NET_SERVICE::color = network::protocol::PlayerColor::Error;

    EngineStatus NET_SERVICE::initialize() {
        this->running = true;
        this->connect = false;
        this->thread = new std::thread(&NET_SERVICE::run, std::ref(*this));
        return EngineStatus::Continue;
    }

    EngineStatus NET_SERVICE::earlyUpdate() {
        auto gm = this->engine->findService<GAME_SERVICE>();
        auto scope = gm->currentScope();
        if (scope == nullptr) return EngineStatus::Continue;
        this->mut_in.lock();
        for (auto &entry : scope->entityManager.entities) {
            for (auto &entity : entry.second) {
                switch (entity->type) {
                    case network::protocol::Type::BOSS_LEFTPART:
                    case network::protocol::Type::BOSS_MIDDLEPART:
                    case network::protocol::Type::BOSS_RIGHTPART:
                    case network::protocol::Type::SHIP_WING:
                    case network::protocol::Type::SHIP_ARC:
                    case network::protocol::Type::SHIP_INTERCEPTOR:
                    case network::protocol::Type::SHIP_TIEADVANCE:
                    case network::protocol::Type::SHIP_TIEAVENGER:
                    case network::protocol::Type::SHIP_TIEBOMBER:
                    case network::protocol::Type::SHIP_TIEEXPERIMENT:
                    case network::protocol::Type::SHIP_TIEFIGHTER:
                    case network::protocol::Type::SHIP_XWING:
                    case network::protocol::Type::SHIP_YWING : {
                        auto ship = new network::protocol::SShip{
                                {
                                        {
                                                {
                                                        entity->updateType,
                                                        entity->type,
                                                        entity->refreshTime,
                                                        entity->id,
                                                        network::protocol::Action::Update,
                                                        sizeof(network::protocol::SShip),
                                                        entity->playerColor
                                                },
                                                entity->isEnabled,
                                                entity->position.x,
                                                entity->position.y
                                        },
                                        ((MOVABLE_ENTITY *) entity)->speed.x,
                                        ((MOVABLE_ENTITY *) entity)->speed.y
                                },
                                ((::Entities::Ship *) entity)->team,
                                ((::Entities::Ship *) entity)->health,
                                ((::Entities::Ship *) entity)->shield
                        };
                        this->in.push(&ship->base.base.header);
                        break;
                    }
                    case network::protocol::Type::LASER1:
                    case network::protocol::Type::LASER2:
                    case network::protocol::Type::LASER3:
                    case network::protocol::Type::LASER4: {
                        auto projectile = new network::protocol::SProjectile{
                                {
                                        {
                                                {
                                                        entity->updateType,
                                                        entity->type,
                                                        entity->refreshTime,
                                                        entity->id,
                                                        network::protocol::Action::Update,
                                                        sizeof(network::protocol::SProjectile),
                                                        entity->playerColor
                                                },
                                                entity->isEnabled,
                                                entity->position.x,
                                                entity->position.y
                                        },
                                        ((MOVABLE_ENTITY *) entity)->speed.x,
                                        ((MOVABLE_ENTITY *) entity)->speed.y
                                },
                                ((::Entities::Projectile *) entity)->originTeam,
                                ((::Entities::Projectile *) entity)->damage
                        };
                        this->in.push(&projectile->base.base.header);
                        break;
                    }
                    case network::protocol::Type::ASTEROID_BIG:
                    case network::protocol::Type::ASTEROID_MED:
                    case network::protocol::Type::ASTEROID_SMALL:
                    case network::protocol::Type::ASTEROID_TINY: {
                        auto asteroid = new network::protocol::SMovable{
                                {
                                        {
                                                entity->updateType,
                                                entity->type,
                                                entity->refreshTime,
                                                entity->id,
                                                network::protocol::Action::Update,
                                                sizeof(network::protocol::SMovable),
                                                entity->playerColor
                                        },
                                        entity->isEnabled,
                                        entity->position.x,
                                        entity->position.y
                                },
                                ((MOVABLE_ENTITY *) entity)->speed.x,
                                ((MOVABLE_ENTITY *) entity)->speed.y
                        };
                        this->in.push(&asteroid->base.header);
                        break;
                    }
                    case network::protocol::Type::POWERUP_DAMAGE:
                    case network::protocol::Type::POWERUP_HEAL:
                    case network::protocol::Type::POWERUP_SHIELD:
                    case network::protocol::Type::POWERUP_SPEED: {
                        auto powerup = new network::protocol::SPowerUp{
                                {
                                        {
                                                {
                                                        entity->updateType,
                                                        entity->type,
                                                        entity->refreshTime,
                                                        entity->id,
                                                        network::protocol::Action::Update,
                                                        sizeof(network::protocol::SPowerUp),
                                                        entity->playerColor
                                                },
                                                entity->isEnabled,
                                                entity->position.x,
                                                entity->position.y
                                        },
                                        ((MOVABLE_ENTITY *) entity)->speed.x,
                                        ((MOVABLE_ENTITY *) entity)->speed.y
                                },
                                ((::Entities::APowerUp *) entity)->grade
                        };
                        this->in.push(&powerup->base.base.header);
                        break;
                    }
                }
            }
        }
        this->mut_in.unlock();
        return EngineStatus::Continue;
    }

    EngineStatus NET_SERVICE::update() {
        return EngineStatus::Continue;
    }

    EngineStatus NET_SERVICE::lateUpdate() {
        auto gm = this->engine->findService<GAME_SERVICE>();
        auto scope = gm->currentScope();
        if (scope == nullptr) return EngineStatus::Continue;
        this->mut_out.lock();
        while (!this->out.empty()) {
            auto p = this->out.front();

            auto e = scope->entityManager.find(p->id);
            if (e == nullptr) {
//                scope->entityManager.netAdd(LAYER::Layer1, p->color, )
            } else {
                switch (p->type) {
                    case network::protocol::Type::ASTEROID_BIG:
                    case network::protocol::Type::ASTEROID_MED:
                    case network::protocol::Type::ASTEROID_SMALL:
                    case network::protocol::Type::ASTEROID_TINY: {
                        auto obj = reinterpret_cast<MOVABLE_ENTITY *>(e);
                        auto data = reinterpret_cast<network::protocol::SMovable *>(p);
                        obj->position.x = data->base.pos_x;
                        obj->position.y = data->base.pos_y;
                        obj->isEnabled = data->base.isEnabled;
                        obj->speed.x = data->speed_x;
                        obj->speed.y = data->speed_y;
                        break;
                    }
                    case network::protocol::Type::POWERUP_DAMAGE:
                    case network::protocol::Type::POWERUP_HEAL:
                    case network::protocol::Type::POWERUP_SHIELD:
                    case network::protocol::Type::POWERUP_SPEED: {
                        auto obj = reinterpret_cast<::Entities::APowerUp *>(e);
                        auto data = reinterpret_cast<network::protocol::SPowerUp *>(p);
                        obj->position.x = data->base.base.pos_x;
                        obj->position.y = data->base.base.pos_y;
                        obj->isEnabled = data->base.base.isEnabled;
                        obj->speed.x = data->base.speed_x;
                        obj->speed.y = data->base.speed_y;
                        obj->grade = (GRADE) data->grade;
                        break;
                    }
                    case network::protocol::Type::LASER1:
                    case network::protocol::Type::LASER2:
                    case network::protocol::Type::LASER3:
                    case network::protocol::Type::LASER4: {
                        auto obj = reinterpret_cast<::Entities::Projectile *>(e);
                        auto data = reinterpret_cast<network::protocol::SProjectile *>(p);
                        obj->position.x = data->base.base.pos_x;
                        obj->position.y = data->base.base.pos_y;
                        obj->isEnabled = data->base.base.isEnabled;
                        obj->speed.x = data->base.speed_x;
                        obj->speed.y = data->base.speed_y;
                        obj->damage = data->damage;
                        obj->originTeam = (::Entities::Ship::TEAM) data->team;
                        break;
                    }
                    case network::protocol::Type::BOSS_LEFTPART:
                    case network::protocol::Type::BOSS_MIDDLEPART:
                    case network::protocol::Type::BOSS_RIGHTPART:
                    case network::protocol::Type::SHIP_WING:
                    case network::protocol::Type::SHIP_ARC:
                    case network::protocol::Type::SHIP_INTERCEPTOR:
                    case network::protocol::Type::SHIP_TIEADVANCE:
                    case network::protocol::Type::SHIP_TIEAVENGER:
                    case network::protocol::Type::SHIP_TIEBOMBER:
                    case network::protocol::Type::SHIP_TIEEXPERIMENT:
                    case network::protocol::Type::SHIP_TIEFIGHTER:
                    case network::protocol::Type::SHIP_XWING:
                    case network::protocol::Type::SHIP_YWING: {
                        auto obj = reinterpret_cast<::Entities::Ship *>(e);
                        auto data = reinterpret_cast<network::protocol::SShip *>(p);
                        obj->position.x = data->base.base.pos_x;
                        obj->position.y = data->base.base.pos_y;
                        obj->isEnabled = data->base.base.isEnabled;
                        obj->speed.x = data->base.speed_x;
                        obj->speed.y = data->base.speed_y;
                        obj->team = (::Entities::Ship::TEAM) data->team;
                        obj->health = data->health;
                        obj->shield = data->shield;
                        break;
                    }
                }
            }
            this->out.pop();
            delete[] reinterpret_cast<char*>(p);
        }
        this->mut_out.unlock();
        return EngineStatus::Continue;
    }

    EngineStatus NET_SERVICE::shutdown() {
        this->running = false;
        this->thread->join();
        delete this->thread;
        return EngineStatus::Continue;
    }

    void NET_SERVICE::runRead() {
        std::unique_ptr<mysocket::Socket> sock;
        mysocket::InetAddr server{};
        char buf[1024];

        try {
            sock = std::make_unique<mysocket::Socket>(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
            sock->setAddress(43000, "0.0.0.0");
            if (sock->Bind() == -1)
                return ;
        }
        catch (mysocket::SocketException const& e) {
            sock.reset(nullptr);
        }
        catch (...) {
            sock.reset(nullptr);
        }

        while (this->running.load()) {
            int len = 0;
            if ((len = sock->RecvFrom(buf, 1024, MSG_DONTWAIT, server)) >= 0) {
                auto* hdr = reinterpret_cast<network::protocol::Header*>(buf);
                auto* odr = reinterpret_cast<network::protocol::ObjectHeader*>(hdr + 1);
                auto* tp = new char[odr->size];
                std::memcpy(tp, odr, odr->size);
                mut_out.lock();
                out.push(reinterpret_cast<network::protocol::ObjectHeader*>(tp));
                mut_out.unlock();
            }
        }
    }

    void NET_SERVICE::run() {
        bool ok = false;
        std::unique_ptr<mysocket::Socket> sock;
        mysocket::InetAddr server{};

        std::thread t(&NET_SERVICE::runRead, std::ref(*this));

        while (!ok && this->running.load()) {
            while (!connect.load() && this->running.load()) {}
            try {
                sock = std::make_unique<mysocket::Socket>(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
                server.SetAddress(address);
                server.SetPort(port);
                ok = true;
            }
            catch (mysocket::SocketException const& e) {
                sock.reset(nullptr);
            }
            catch (...) {
                sock.reset(nullptr);
            }
        }
        while (this->running.load()) {
            mut_in.lock();
            while (!this->in.empty()) {
                auto p = this->in.front();

                network::protocol::Header hdr{};
                hdr.size = p->size;
                hdr.type = network::protocol::HeaderType::Object;
                std::basic_string<unsigned char> msg;
                msg.append(reinterpret_cast<unsigned char*>(&hdr), sizeof(network::protocol::Header));
                msg.append(reinterpret_cast<unsigned char*>(p), p->size);
                
                sock->SendTo(msg.data(), p->size + sizeof(network::protocol::Header), 0, server);

                this->in.pop();
                delete p;
            }
            mut_in.unlock();
        }
        if (t.joinable())
            t.join();
    }

    network::protocol::Status NET_SERVICE::connectTCP(std::string const& name,
                                                      std::string const& passwd,
                                                      std::string const& ipAddr) {

        try {
            mysocket::Socket tc{AF_INET, SOCK_STREAM, IPPROTO_TCP};
            network::protocol::Header hdr{};
            network::protocol::Connexion connect{};
            hdr.type = network::protocol::HeaderType::Connect;
            hdr.size = sizeof(network::protocol::Connexion);
            std::strncpy(connect.name, name.c_str(), 256);
            std::strncpy(connect.pass, passwd.c_str(), 256);
            tc.setAddress(42000, ipAddr);
            if (tc.Connect() == -1) {
                // LOG
                return network::protocol::Status::Error;
            }
            std::basic_string<unsigned char> msg;
            msg.append(reinterpret_cast<unsigned char*>(&hdr), sizeof(network::protocol::Header));
            msg.append(reinterpret_cast<unsigned char*>(&connect), hdr.size);
            if (tc.Send(msg.data(), msg.length(), 0) == -1) {
                // LOG
                return network::protocol::Status::Error;
            }
            network::protocol::Header mdr{};
            network::protocol::ConnexionResponse resp{};
            if (tc.Recv(&mdr, sizeof(mdr)) == -1) {
                // LOG
                return network::protocol::Status::Error;
            }
            if (tc.Recv(&resp, sizeof(resp)) == -1) {
                // LOG
                return network::protocol::Status::Error;
            }
            if (resp.status >= network::protocol::Status::Error) {
                // LOG
                return resp.status;
            }
            this->color = resp.color;
            this->address = ipAddr;
            this->port = resp.port;
            this->connect = true;
            return resp.status;
        }
        catch (mysocket::SocketException const& e) {
            // LOG
            return network::protocol::Status::Error;
        }
        catch (...) {
            return network::protocol::Status::Error;
        }
    }
}