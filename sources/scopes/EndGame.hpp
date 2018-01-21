#pragma once

#include "imgui.h"
#include "engine/ForwardDeclaration.hpp"
#include "engine/service/GameService.hpp"
#include "MenuScope.hpp"
#include <engine/ForwardDeclaration.hpp>

namespace Scopes {
    class EndGame : public SCOPE {
    public:
        explicit EndGame(GAME_SERVICE *gameService) :
                SCOPE(gameService) {}

        ~EndGame() = default;


        void initialize() override {
        }

        void pause() override {
        }

        void resume() override {
        }

        void shutdown() override {
        }

        void update() override {

            ImGui::Begin("Game Over");
            ImGui::SetWindowPos(ImVec2(this->gameService->getWindowSize().x/2 - 50, this->gameService->getWindowSize().y/2 - 50));
            if (ImGui::Button("Main Menu")){
                this->gameService->pushScope<Scopes::MenuScope>();
            }
            if (ImGui::Button("Quit Game")){
                this->gameService->popScope();
            }
            ImGui::End();
        }
    };
}