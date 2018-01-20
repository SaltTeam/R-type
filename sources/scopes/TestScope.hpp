
#pragma once

#include <imgui.h>
#include "entities/PlayerShip.hpp"
#include "entities/Asteroid.hpp"
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

namespace Scopes {
    class TestScope : public SCOPE {
    public:
        explicit TestScope(GAME_SERVICE *gameService) : SCOPE(gameService) {}

        ~TestScope() override = default;

        void spawnBoss(SCOPE *scope, int x, int y)
        {
            scope->entityManager.add<Entities::LeftPart>(LAYER::Layer1, scope, 10, true, x, y + 131);
            scope->entityManager.add<Entities::MiddlePart>(LAYER::Layer1, scope, 10, true, x + 16, y);
            scope->entityManager.add<Entities::RightPart>(LAYER::Layer1, scope, 10, true, x + 200, y + 131);
        }

        void initialize() override {
            this->entityManager.add<Entities::SpeedPowerUp>(LAYER::Layer1, this, 9, GOLD, 100, 0);
            this->entityManager.add<Entities::YWing>(LAYER::Layer1, this, 0, true, 250, 600);
            this->entityManager.add<Entities::TieBomber>(LAYER::Layer1, this, 10);

            spawnBoss(this, 125, 0);
        }

        void pause() override {
        }

        void resume() override {
        }

        void shutdown() override {
        }

        void update() override {
            ImGui::Begin("Hello, world!");
            ImGui::Button("Look at this pretty button");
            ImGui::End();
        }
    };

    class MenuScope : public SCOPE {
    public:
        MenuScope(GAME_SERVICE *gameService) : SCOPE(gameService) {}
        ~MenuScope() {}



        void initialize() override {

        }
    };
}
