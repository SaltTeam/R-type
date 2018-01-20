
#include <entities/projectiles/Projectile.hpp>
#include <entities/powerups/APowerUp.hpp>
#include "NetService.hpp"
#include "engine/Runner.hpp"
#include "engine/entity/Entity.hpp"
#include "entities/ships/Ship.hpp"
#include "engine/scope/Scope.hpp"
#include "engine/service/GameService.hpp"

namespace Engine {
    EngineStatus NET_SERVICE::initialize() {
        this->running = true;
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
                                                        sizeof(network::protocol::SShip)
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
                                                sizeof(network::protocol::SShip)
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
                                                        sizeof(network::protocol::SShip)
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
        this->mut_in.lock();
        std::cout << this->in.size() << std::endl;
        this->mut_in.unlock();
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
        while (this->running.load()) {
            mut_in.lock();
            while (!this->in.empty()) {
                auto p = this->in.front();
                std::cout << (short) p->type << std::endl;
                this->in.pop();
                // send packet
                delete p;
            }
            mut_in.unlock();
        }
    }
}