# pragma once

#include "imgui.h"
#include "engine/ForwardDeclaration.hpp"
#include "engine/service/GameService.hpp"
#include "ShipChoiceScope.hpp"

namespace Scopes {

    class MenuScope : public SCOPE {
    private:
        bool setting = false;

    public:
        explicit MenuScope(GAME_SERVICE *gameService) : SCOPE(gameService) {}

        ~MenuScope() override = default;


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
            ImGui::SetWindowPos(ImVec2(500, 700));
            if (ImGui::Button("Play", ImVec2(100, 50))) {
                this->gameService->pushScope<Scopes::ShipChoiceScope>();
            }
            if (ImGui::Button("Settings", ImVec2(100, 50))) {
               if (!setting)
                   setting = true;
               else
                   setting = false;
            }
            if (ImGui::Button("Quit",  ImVec2(100, 50))) {
                std::cout << "Quit" << std::endl;
                this->gameService->clear();
            }
            if (setting) {
                ImGui::Begin("Settings");
                ImGui::SetWindowPos(ImVec2(300, 700));
                ImGui::SetWindowSize(ImVec2(150, 200));
                ImGui::Button("Sound", ImVec2(100, 50));
                ImGui::Button("Graphics", ImVec2(100, 50));
                ImGui::Button("Difficulty", ImVec2(100, 50));
                ImGui::End();
            }
            ImGui::End();
        }
    };
}