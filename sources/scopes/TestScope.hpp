
#pragma once

#include <imgui.h>
#include <entities/ships/sub/TieFigther.hpp>
#include <entities/ships/sub/TieBomber.hpp>
#include <entities/powerups/sub/HealPowerUp.hpp>
#include <entities/powerups/sub/SpeedPowerUp.hpp>
#include <entities/ships/sub/TieExperiment.hpp>
#include <entities/ships/sub/TieAvenger.hpp>
#include <entities/ships/Boss/RightPart.hpp>
#include <entities/ships/Boss/MiddlePart.hpp>
#include <entities/ships/Boss/LeftPart.hpp>
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
#include "engine/service/NetService.hpp"

namespace Scopes {
    class TestScope : public SCOPE {
    public:
        explicit TestScope(GAME_SERVICE *gameService) : SCOPE(gameService) {}

        ~TestScope() override = default;

        void spawnBoss(SCOPE *scope, int x, int y)
        {
            scope->entityManager.add<Entities::LeftPart>(LAYER::Layer3, network::protocol::Update::Master, 250, true, x, y + 131);
            scope->entityManager.add<Entities::MiddlePart>(LAYER::Layer3, network::protocol::Update::Master, 250, true, x + 16, y);
            scope->entityManager.add<Entities::RightPart>(LAYER::Layer3, network::protocol::Update::Master, 250, true, x + 200, y + 131);
        }

        void initialize() override {
            createStarfield(this, 70);
            Scopes::createShip(this);
            if (NET_SERVICE::color == network::protocol::PlayerColor::Blue)
            {
                this->entityManager.add<Entities::TieBomber>(LAYER::Layer3, network::protocol::Update::Master, 250);
                spawnBoss(this, 125, 0);
            }
        }

        void pause() override {
        }

        void resume() override {
        }

        void shutdown() override {
        }

        void update() override {
        }
    };
}
