
#pragma once

#include <stack>
#include <random>

#include "engine/ForwardDeclaration.hpp"
#include "engine/scope/Scope.hpp"
#include "engine/service/GraphicalService.hpp"
#include "engine/service/Service.hpp"

namespace Engine {
    namespace Services {
        class GameService : public SERVICE {
            friend ENGINE;
            friend SERVICE_MANAGER;
            friend GRAPHICAL_SERVICE;

        private:
            bool removeScope = false;
            bool addScope = false;
            SCOPE *scopeToAdd = nullptr;

            std::stack<SCOPE *> scopes;

        public:
            template<typename T>
            void registerBaseScope() {
                if (this->scopes.empty())
                    this->scopes.push(new T(this));
            }

            template<typename T>
            void pushScope() {
                this->scopeToAdd = new T(this);
                this->addScope = true;
            }

            void popScope() {
                this->removeScope = true;
            }

            void clear() {
                while (!scopes.empty())
                    scopes.pop();
            }

            void returnMain() {
                while (scopes.size() != 1){
                    scopes.pop();
                }
            }

            SCOPE *currentScope() {
                if (this->scopes.empty())
                    return nullptr;
                return this->scopes.top();
            }

            sf::Vector2u getWindowSize();

        private:
            explicit GameService(ENGINE *e) : SERVICE(e) {}

            ~GameService() override = default;

            EngineStatus initialize() override;

            EngineStatus shutdown() override;

            EngineStatus earlyUpdate() override;

            EngineStatus update() override;

            EngineStatus lateUpdate() override;

            void execCallbacks();
        };
    };
}
