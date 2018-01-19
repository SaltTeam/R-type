
#pragma once

#include <entities/ships/sub/TieFigther.hpp>
#include <entities/ships/sub/TieBomber.hpp>
#include <entities/powerups/sub/HealPowerUp.hpp>
#include <entities/powerups/sub/SpeedPowerUp.hpp>
#include <entities/ships/sub/TieExperiment.hpp>
#include <entities/ships/sub/TieAvenger.hpp>
#include "entities/ships/sub/YWing.hpp"
#include "entities/ships/sub/XWing.hpp"
#include "entities/ships/sub/_Wing.hpp"
#include "entities/ships/sub/Arc.hpp"
#include "entities/ships/sub/Interceptor.hpp"
#include "entities/Asteroid.hpp"
#include "engine/ForwardDeclaration.hpp"
#include "engine/service/GameService.hpp"

namespace Scopes {
    class TestScope : public SCOPE {
    public:
        explicit TestScope(GAME_SERVICE *gameService) : SCOPE(gameService) {}

        ~TestScope() override = default;

        void initialize() override {
            this->entityManager.add<Entities::SpeedPowerUp>(LAYER::Layer1, this, 9, GOLD, 100, 0);
            this->entityManager.add<Entities::YWing>(LAYER::Layer1, this, 0, true, 250, 600);
            this->entityManager.add<Entities::TieBomber>(LAYER::Layer1, this, 10);
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
