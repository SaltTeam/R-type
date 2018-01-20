//
// Created by vivaldi91 on 19/01/18.
//

#pragma once

#include <imgui.h>
#include <imgui-SFML.h>
#include <array>
#include "scopes/TestScope.hpp"
#include "engine/Runner.hpp"
#include "engine/service/NetService.hpp"

namespace Scopes {
    class LoginScope : public SCOPE {
    private:
        bool setting = false;
        std::array<char, 256> buf;
        std::array<char, 256> passwd;
        std::array<char, 256> ip;
        std::string error_message = "";
        int status = 200;

    public:
        LoginScope(GAME_SERVICE *gameService) : SCOPE(gameService) {
             }

        ~LoginScope() = default;


        void initialize() override {
            buf[0] = '\0';
            passwd[0] = '\0';
            ip[0] = '\0';
        }

        void pause() override {
        }

        void resume() override {
        }

        void shutdown() override {
        }

        void update() override {

            ImGui::Begin("Login");
            ImGui::Text(this->error_message.c_str());
            ImGui::SetWindowPos(ImVec2(300, 300));
            ImGui::SetWindowSize(ImVec2(300, 250));
            ImGui::InputText("Ip", ip.data(), 256);
            ImGui::InputText("Game", buf.data(), 256);
            ImGui::InputText("Password", passwd.data(), 256,ImGuiInputTextFlags_Password);
            if (ImGui::Button("Validate", ImVec2(75, 20)))
            {
                std::cout << buf.data() << std::endl;
                std::cout << passwd.data() << std::endl;

                status = static_cast<int>(gameService->engine->findService<NET_SERVICE>()->connectTCP(buf.data(),
                                                                                                      passwd.data(),
                                                                                                      ip.data()));
                switch (status)
                {
                    case(200):
                        this->gameService->pushScope<Scopes::TestScope>();
                        break;
                    case(500):
                        this->error_message = "An error Occured please try again later";
                        break;
                    case(501):
                        this->error_message = "Wrong Password try again please";
                        break;
                    case(502):
                        this->error_message = "Sorry, the game you are trying to join is Full";
                        break;
                    default:
                        break;
                }
            }
            ImGui::End();
        }
    };
}
