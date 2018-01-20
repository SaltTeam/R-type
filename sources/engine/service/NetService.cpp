
#include "entities/projectiles/Projectile.hpp"
#include "entities/powerups/APowerUp.hpp"
#include "NetService.hpp"
#include "engine/Runner.hpp"
#include "engine/entity/Entity.hpp"
#include "entities/ships/Ship.hpp"
#include "engine/scope/Scope.hpp"
#include "engine/service/GameService.hpp"

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
                    case network::protocol::Type::SHIP : {
                        auto ship = new network::protocol::SShip{
                                {
                                        {
                                                {
                                                        entity->updateType,
                                                        entity->type,
                                                        entity->refreshTime,
                                                        entity->id,
                                                        network::protocol::Action::Update,
                                                        sizeof(network::protocol::SShip)
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
                    case network::protocol::Type::PROJECTILE: {
                        auto projectile = new network::protocol::SProjectile{
                                {
                                        {
                                                {
                                                        entity->updateType,
                                                        entity->type,
                                                        entity->refreshTime,
                                                        entity->id,
                                                        network::protocol::Action::Update,
                                                        sizeof(network::protocol::SProjectile)
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
                    case network::protocol::Type::ASTEROID: {
                        auto asteroid = new network::protocol::SMovable{
                                {
                                        {
                                                entity->updateType,
                                                entity->type,
                                                entity->refreshTime,
                                                entity->id,
                                                network::protocol::Action::Update,
                                                sizeof(network::protocol::SMovable)
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
                    case network::protocol::Type::POWERUP: {
                        auto powerup = new network::protocol::SPowerUp{
                                {
                                        {
                                                {
                                                        entity->updateType,
                                                        entity->type,
                                                        entity->refreshTime,
                                                        entity->id,
                                                        network::protocol::Action::Update,
                                                        sizeof(network::protocol::SPowerUp)
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
        //this->mut_out.lock();
        // Code
        //this->mut_out.unlock();
        return EngineStatus::Continue;
    }

    EngineStatus NET_SERVICE::shutdown() {
        this->running = false;
        this->thread->join();
        delete this->thread;
        return EngineStatus::Continue;
    }

    void NET_SERVICE::run() {
        bool ok = false;
        std::unique_ptr<mysocket::Socket> sock;
        mysocket::InetAddr server{};

        while (!ok) {
            while (!connect.load()) {}
            try {
                sock = std::make_unique<mysocket::Socket>(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
                sock->setAddress(43000, "0.0.0.0");
                if (sock->Bind() == -1)
                    throw std::exception();
                server.SetPort(this->port);
                server.SetAddress(this->address);
                ok = true;
            }
            catch (mysocket::SocketException const &e) {
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
                this->in.pop();

                network::protocol::Header hdr{};
                hdr.size = p->size;
                hdr.type = network::protocol::HeaderType::Object;
                std::basic_string<unsigned char> msg;
                msg.append(reinterpret_cast<unsigned char *>(&hdr), sizeof(network::protocol::Header));
                msg.append(reinterpret_cast<unsigned char *>(p), p->size);

                sock->SendTo(msg.data(), p->size + sizeof(network::protocol::Header), 0, server);

                delete p;
            }
            mut_in.unlock();
        }
    }

    network::protocol::Status NET_SERVICE::connectTCP(std::string const &name,
                                                      std::string const &passwd,
                                                      std::string const &ipAddr) {

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
            msg.append(reinterpret_cast<unsigned char *>(&hdr), sizeof(network::protocol::Header));
            msg.append(reinterpret_cast<unsigned char *>(&connect), hdr.size);
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
        catch (mysocket::SocketException const &e) {
            // LOG
            return network::protocol::Status::Error;
        }
        catch (...) {
            return network::protocol::Status::Error;
        }
    }
}