
#pragma once

#include "entities/ships/YWing.hpp"
#include "entities/ships/XWing.hpp"
#include "entities/ships/_Wing.hpp"
#include "entities/ships/Arc.hpp"
#include "entities/ships/Intercepteur.hpp"
#include "entities/Asteroid.hpp"
#include "engine/ForwardDeclaration.hpp"
#include "engine/service/GameService.hpp"

namespace Scopes {
    class TestScope : public SCOPE {
    public:
        explicit TestScope(GAME_SERVICE *gameService) : SCOPE(gameService) {}

        ~TestScope() override = default;

        void initialize() override {
            this->entityManager.add<Entities::YWing>(LAYER::Layer1, this, 0, true, 350, 350);
	    this->entityManager.add<Entities::XWing>(LAYER::Layer1, this, 1, true, 150, 150);
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
