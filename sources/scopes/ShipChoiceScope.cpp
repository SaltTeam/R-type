#include <entities/ships/sub/YWing.hpp>
#include <entities/ships/sub/_Wing.hpp>
#include <entities/ships/sub/Interceptor.hpp>
#include <entities/ships/sub/Arc.hpp>
#include "entities/ships/sub/XWing.hpp"
#include "ShipChoiceScope.hpp"
#include "LoginScope.hpp"

namespace Scopes {
    int ShipChoiceScope::g_Ship = 0;
    void ShipChoiceScope::update() {
        static int cpt = 0;
        static bool button = true;
        static std::string desc(" ");
        static std::string stat(" ");
        static std::string name(" ");

        if (button) {
            switch (cpt) {
                case 0:
                    if (this->entityManager.entities.size() > 0)
                        this->removeEntity(this->entityManager.entities.begin()->second.front());
                    this->entityManager.add<Entities::XWing>(LAYER::Layer1, network::protocol::Update::Replica, 1000, true,
                                                             this->gameService->getWindowSize().x / 2 - 50, 300);
                    g_Ship = cpt;
                    desc = "The Xwing is a quite fast ship,\nbut he is also large and quite long.\nWith a fast speed and common damage\nit will be a must have\nfor an advanced player.";
                    stat = "HP = 100\nSpeed = Fast\nDamage = 10\nWeapons = Laser1\nShield = 0";
                    name = "XWing";
                    break;
                case 1:
                    if (this->entityManager.entities.size() > 0)
                        this->removeEntity(this->entityManager.entities.begin()->second.front());
                    this->entityManager.add<Entities::YWing>(LAYER::Layer1, network::protocol::Update::Replica, 1000, true,
                                                             this->gameService->getWindowSize().x / 2 - 50, 300);
                    g_Ship = cpt;
                    desc = "The Ywing is a very special figther\nand a quite long one.\nWith a slow speed,\nhigh damage and great HP\nthis ship will definitely\nbe your safest choice.";
                    stat = "HP = 200\nSpeed = Low\nDamage = 50\nWeapons = Laser2\nShield = 0";
                    name = "YWing";
                    break;
                case 2:
                    if (this->entityManager.entities.size() > 0)
                        this->removeEntity(this->entityManager.entities.begin()->second.front());
                    this->entityManager.add<Entities::_Wing>(LAYER::Layer1, network::protocol::Update::Replica, 1000, true,
                                                             this->gameService->getWindowSize().x / 2 - 50, 300);
                    g_Ship = cpt;
                    desc = "The wing is a common figther,\nbut a bit large.\nWith an average speed\nand common damage\nit will be your best choice to learn\nthe basics of the game.";
                    stat = "HP = 100\nSpeed = Average\nDamage = 10\nWeapons = Laser1\nShield = 0";
                    name = "Wing";
                    break;
                case 3:
                    if (this->entityManager.entities.size() > 0)
                        this->removeEntity(this->entityManager.entities.begin()->second.front());
                    this->entityManager.add<Entities::Interceptor>(LAYER::Layer1, network::protocol::Update::Replica, 1000, true,
                                                                   this->gameService->getWindowSize().x / 2 - 50, 300);
                    g_Ship = cpt;
                    desc = "The Interceptor is our most special ship,\nhe is the tiniest and the fastest\nship available. \nThis ship has low damage and health \nso all of your gameplay will have\nto be focused\non dodging.";
                    stat = "HP = 75\nSpeed = Fast\nDamage = 8\nWeapons = Laser3\nShield = 25";
                    name = "Interceptor";
                    break;
                case 4:
                    if (this->entityManager.entities.size() > 0)
                        this->removeEntity(this->entityManager.entities.begin()->second.front());
                    this->entityManager.add<Entities::Arc>(LAYER::Layer1, network::protocol::Update::Replica, 1000, true,
                                                           this->gameService->getWindowSize().x / 2 - 50, 300);
                    g_Ship = cpt;
                    desc = "At first the arc look like\na quite common ship\nand that this ship can\noffer you a pretty special gameplay.";
                    stat = "HP = 100\nSpeed = Fast\nDamage = 5\nWeapons = Laser4\nShield = 0";
                    name = "Arc";
                    break;
                default:
                    cpt = 0;
                    break;
            }
            button = false;
        }
        ImGui::Begin("Ship Stats");
        ImGui::SetWindowSize(ImVec2(200, 100));
        ImGui::SetWindowPos(ImVec2(50, 700));
        ImGui::Text(stat.c_str());
        ImGui::End();

        ImGui::Begin("Description");
        ImGui::SetWindowSize(ImVec2(300, 400));
        ImGui::SetWindowPos(ImVec2(400, 700));
        ImGui::Text(name.c_str());
        ImGui::Text(desc.c_str());
        ImGui::End();

        ImGui::Begin("Selection");
        ImGui::SetWindowSize(ImVec2(90, 120));
        if (ImGui::Button("Next")) {
            cpt++;
            button = true;
        }
        if (ImGui::Button("Prev")) {
            if (cpt == 0)
                cpt = 4;
            else
                cpt--;
            button = true;

        };
        if (ImGui::Button("Select")) {
            this->entityManager.entities.clear();
            this->gameService->pushScope<Scopes::LoginScope>();
            button = true;
        }
        if (ImGui::Button("Solo")) {
            this->entityManager.entities.clear();
            this->gameService->pushScope<Scopes::Level1Scope>();
            NET_SERVICE::color = network::protocol::PlayerColor::Blue;
        }
        ImGui::End();

    }
}