# pragma once

#include "imgui.h"
#include "engine/ForwardDeclaration.hpp"
#include "engine/service/GameService.hpp"

namespace Scopes {

    class MenuScope : public SCOPE {
    public:
        MenuScope(GAME_SERVICE *gameService) : SCOPE(gameService) {}

        ~MenuScope() = default;


        void initialize() override {
        }

        void pause() override {
        }

        void resume() override {
        }

        void shutdown() override {
        }

        void update() override {
            ImGui::Begin("R-type");
            //ImGui::SetWindowSize(ImVec2(this->gameService->getWindowSize().x, this->gameService->getWindowSize().y));
            ImGui::SetWindowPos(ImVec2(0, 30));
            if (ImGui::Button("Play")) {
                std::cout << "Play" << std::endl;
            }
            ImGui::End();
        }

    };
}