
#pragma once

#include <entities/ships/sub/Enemy1.hpp>
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
            this->entityManager.add<Entities::Arc>(LAYER::Layer1, this, 0, true, 0, 200);
            this->entityManager.add<Entities::Enemy1>(LAYER::Layer1, this, 10);
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
