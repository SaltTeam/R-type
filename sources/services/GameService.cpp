
#include "GameService.hpp"

#include <iostream>

namespace Services {
    GameService::GameService(Engine *e) : BaseService(e) {
        std::cout << "GameService: constructor." << std::endl;
    }

    GameService::~GameService() {
        std::cout << "GameService: destructor." << std::endl;
    }

    void GameService::initialize() {
        std::cout << "GameService: initialize." << std::endl;
        this->scopes.elements.front()->initialize();
    }

    void GameService::shutdown() {
        std::cout << "GameService: shutdown." << std::endl;
        this->scopes.execute(&Scopes::BaseScope::shutdown);
    }

    void GameService::earlyUpdate() {
        std::cout << "GameService: earlyUpdate." << std::endl;

        /// Check for adding Scope
        if (this->addScope) {
            this->scopes.elements.push_back(scopeToAdd);
            this->scopeToAdd->initialize();
            this->addScope = false;
            this->scopeToAdd = nullptr;
        }

        this->scopes.elements.back()->earlyUpdate();
    }

    void GameService::update() {
        std::cout << "GameService: update." << std::endl;

        scopes.elements.back()->update();
    }

    void GameService::lateUpdate() {
        std::cout << "GameService: lateUpdate." << std::endl;

        scopes.elements.back()->lateUpdate();

        /// Check for removing Scope
        if (this->removeScope) {
            this->removeScope = false;
            this->scopes.elements.back()->shutdown();
            delete this->scopes.elements.back();
            this->scopes.elements.pop_back();
        }
    }
}
