
#pragma once

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

        void shutdown() override {
            std::cout << "EmptyScope: shutdown." << std::endl;
        }

        void earlyUpdate() override {
            std::cout << "EmptyScope: earlyUpdate." << std::endl;
        }

        void update() override {
            std::cout << "EmptyScope: update." << std::endl;
        }

        void lateUpdate() override {
            std::cout << "EmptyScope: lateUpdate." << std::endl;
        }
    };
}
