#include <entities/ships/sub/YWing.hpp>
#include <entities/ships/sub/_Wing.hpp>
#include <entities/ships/sub/Interceptor.hpp>
#include <entities/ships/sub/Arc.hpp>
#include "entities/ships/sub/XWing.hpp"
#include "ShipChoiceScope.hpp"

namespace Scopes {
    void ShipChoiceScope::update() {
        static int cpt = 0;

        switch (cpt) {
            case 0:
                this->entityManager.entities.clear();
                this->entityManager.add<Entities::XWing>(LAYER::Layer1, this, 0, true, this->gameService->getWindowSize().x / 2 - 50, 300);
                break;
            case 1:
                this->entityManager.entities.clear();
                this->entityManager.add<Entities::YWing>(LAYER::Layer1, this, 0, true, this->gameService->getWindowSize().x / 2 - 50, 300);
                break;
            case 2:
                this->entityManager.entities.clear();
                this->entityManager.add<Entities::_Wing>(LAYER::Layer1, this, 0, true, this->gameService->getWindowSize().x / 2 - 50, 300);
                break;
            case 3:
                this->entityManager.entities.clear();
                this->entityManager.add<Entities::Interceptor>(LAYER::Layer1, this, 0, true, this->gameService->getWindowSize().x / 2 - 50, 300);
                break;
            case 4:
                this->entityManager.entities.clear();
                this->entityManager.add<Entities::Arc>(LAYER::Layer1, this, 0, true, this->gameService->getWindowSize().x / 2 - 50, 300);
                break;
            default:
                cpt = 0;
                break;
        }
        ImGui::Begin("Ship Stats");
        ImGui::SetWindowSize(ImVec2(200, 100));
        ImGui::SetWindowPos(ImVec2(50, 700));
        ImGui::Text("Speed: ");
        ImGui::Text("Shield: ");
        ImGui::Text("Power: ");
        ImGui::End();

        ImGui::Begin("Description");
        ImGui::SetWindowSize(ImVec2(200, 200));
        ImGui::SetWindowPos(ImVec2(500, 700));
        ImGui::Text("X-Wing:");
        ImGui::Text("This is the most common\nship in the rebellion");
        ImGui::End();

        ImGui::Begin("Buttons");
        if (ImGui::Button("next")) {
            cpt++;
        }
        if (ImGui::Button("prev")) {
            cpt--;
        };
        ImGui::End();
    }
}