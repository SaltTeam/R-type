
#pragma once

#include <entities/PlayerShip.hpp>
#include "engine/ForwardDeclaration.hpp"
#include "engine/service/GameService.hpp"

namespace Scopes {
    class TestScope : public SCOPE {
    public:
        explicit TestScope(GAME_SERVICE *gameService) : SCOPE(gameService) {}

        ~TestScope() override = default;

        void initialize() override {
            this->entityManager.add<Entities::PlayerShip>(LAYER::Layer1, this, 0, "resources/sprites/ships/player/ship1/base.png");
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
