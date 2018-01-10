
#pragma once

#include "services/GameService.hpp"
#include "scopes/BaseScope.hpp"

namespace Scopes {
    class EmptyScope : public Scopes::BaseScope {
    public:
        explicit EmptyScope(Services::GameService *gameService) : BaseScope(gameService) {}

        ~EmptyScope() override = default;

        void initialize() override {
            std::cout << "EmptyScope: initialize." << std::endl;
        }

        void pause() override {
            std::cout << "EmptyScope: pause." << std::endl;
        }

        void resume() override {
            std::cout << "EmptyScope: resume." << std::endl;
        }

        void shutdown() override {
            std::cout << "EmptyScope: shutdown." << std::endl;
        }

        void update() override {
            std::cout << "EmptyScope: update." << std::endl;
        }
    };
}
