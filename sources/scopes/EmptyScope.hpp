
#pragma once

#include "engine/ForwardDeclaration.hpp"
#include "engine/service/GameService.hpp"

namespace Scopes {
    class EmptyScope : public SCOPE {
    public:
        explicit EmptyScope(GAME_SERVICE *gameService) : SCOPE(gameService) {}

        ~EmptyScope() override = default;

        void initialize() override {
            //entityManager.add<Entities::PlayerShip>(0, "resources/sprites/ships/player/ship1/base.png");
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
