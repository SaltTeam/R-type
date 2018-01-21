//
// Created by 53963 on 21/01/2018.
//

#pragma once

#include <entities/ships/sub/TieFigther.hpp>
#include <entities/ships/sub/TieBomber.hpp>
#include <entities/powerups/sub/HealPowerUp.hpp>
#include <entities/powerups/sub/SpeedPowerUp.hpp>
#include <entities/ships/sub/TieExperiment.hpp>
#include <entities/ships/sub/TieAvenger.hpp>
#include <entities/ships/Boss/RightPart.hpp>
#include <entities/ships/Boss/MiddlePart.hpp>
#include <entities/ships/Boss/LeftPart.hpp>
#include <entities/ships/sub/TieAdvance.hpp>
#include "entities/ships/sub/YWing.hpp"
#include "entities/ships/sub/XWing.hpp"
#include "entities/ships/sub/_Wing.hpp"
#include "entities/ships/sub/Arc.hpp"
#include "entities/ships/sub/Interceptor.hpp"
#include "entities/asteroids/Asteroid.hpp"
#include "engine/ForwardDeclaration.hpp"
#include "engine/service/GameService.hpp"
#include "ShipChoiceScope.hpp"
#include "engine/Runner.hpp"
#include "EndGame.hpp"

namespace Scopes {
    class Level2Scope : public SCOPE {
    private:
        int nb_ships = 0;
        int end = 1;
        int frame = 0;
        std::uniform_int_distribution<std::mt19937::result_type> dist10;
        std::mt19937 rng;


    public:
        explicit Level2Scope(GAME_SERVICE *gameService) : SCOPE(gameService) {}
        ~Level2Scope() override = default;

        void initialize() override {
            this->rng.seed(std::random_device()());
            std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 10000);
            dist10 = dist6;
            Scopes::createShip(this);
            if (this->gameService->engine->findService<NET_SERVICE>()->color == network::protocol::PlayerColor::Blue)
            {
                this->entityManager.add<Entities::TieBomber>(LAYER::Layer3, network::protocol::Update::Master, 250, true, 100, 100);
                this->entityManager.add<Entities::TieBomber>(LAYER::Layer3, network::protocol::Update::Master, 250, true, 300, 100);
                this->nb_ships += 1;
            }
        }

        void pause() override {
        }

        void resume() override {
        }

        void shutdown() override {
        }

        void update() override {
            bool in = true;
            int ennemy_ship = 0;
            frame +=1;
            if (dist10(rng) % 1007 == 0)
                this->entityManager.add<Entities::SmallAsteroid>(LAYER::Layer2, true, 0, 0);
            if (frame == 200 && nb_ships < 5) {
                frame = 0;
                this->entityManager.add<Entities::TieBomber>(LAYER::Layer3,
                                                              network::protocol::Update::Master,
                                                              250, true, 100, 100);
                this->entityManager.add<Entities::TieBomber>(LAYER::Layer3,
                                                             network::protocol::Update::Master,
                                                             250, true, 300, 100);
                nb_ships +=1;
            }
            else if (nb_ships >= 5 && nb_ships < 8) {
                this->entityManager.add<Entities::TieAvenger>(LAYER::Layer3, network::protocol::Update::Master, 250, true, 100, 100);
                this->entityManager.add<Entities::TieAvenger>(LAYER::Layer3, network::protocol::Update::Master, 250, true, 400, 100);
                this->entityManager.add<Entities::TieAvenger>(LAYER::Layer3, network::protocol::Update::Master, 250, true, 100, 300);
                this->entityManager.add<Entities::TieAvenger>(LAYER::Layer3, network::protocol::Update::Master, 250, true, 400, 300);
                nb_ships += 4;
            }
            else {
                for (auto &ship : this->entityManager.entities){
                    in = false;
                    for (auto &it : ship.second)
                    {
                        if (reinterpret_cast<Entities::Ship *>(it)->getTeam() !=
                            Entities::Ship::PLAYER)
                        {
                            ennemy_ship += 1;
                        }
                    }
                }
                if (ennemy_ship == 0 && in == false)
                {
                    if (end == 0)
                    {
                        this->gameService->pushScope<Scopes::EndGameFinal>();
                    }
                    else
                    {
                        this->entityManager.add<Entities::TieAdvance>(LAYER::Layer3, network::protocol::Update::Master, 250, true, 150, 300);
                        this->entityManager.add<Entities::TieAdvance>(LAYER::Layer3, network::protocol::Update::Master, 250, true, 450, 300);
                        this->entityManager.add<Entities::TieAdvance>(LAYER::Layer3, network::protocol::Update::Master, 250, true, 100, 300);
                        this->entityManager.add<Entities::TieAdvance>(LAYER::Layer3, network::protocol::Update::Master, 250, true, 400, 300);
                        end = 0;
                    }
                }
            }
        }
    };
}
