
#pragma once

#include <imgui.h>
#include "entities/PlayerShip.hpp"
#include "entities/Asteroid.hpp"
#include "engine/ForwardDeclaration.hpp"
#include "engine/service/GameService.hpp"

namespace Scopes {
    class TestScope : public SCOPE {
    public:
        explicit TestScope(GAME_SERVICE *gameService) : SCOPE(gameService) {}

        ~TestScope() override = default;

        void initialize() override {
            this->entityManager.add<Entities::PlayerShip>(LAYER::Layer1, this, 0, "resources/sprites/ships/player/ship1/base.png", true, 50, 50);
            this->entityManager.add<Entities::Asteroid>(LAYER::Layer1, this, 0, "resources/sprites/Meteors/meteorGrey_big1.png", true, 50, 50);
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
