
#include "GameService.hpp"

#include <iostream>

namespace Services {
    GameService::GameService(Engine *e) : BaseService(e) {
        std::cout << "GameService: constructor." << std::endl;
    }

    GameService::~GameService() {
        std::cout << "GameService: destructor." << std::endl;
    }

    EngineStatus GameService::initialize() {
        std::cout << "GameService: initialize." << std::endl;
        this->scopes.elements.front()->initialize();
        return EngineStatus::Continue;
    }

    EngineStatus GameService::shutdown() {
        std::cout << "GameService: shutdown." << std::endl;
        this->scopes.execute(&Scopes::BaseScope::shutdown);
        return EngineStatus::Continue;
    }

    EngineStatus GameService::earlyUpdate() {
        std::cout << "GameService: earlyUpdate." << std::endl;

        /// Check for adding Scope
        if (this->addScope) {
            this->scopes.elements.back()->pause();
            this->scopes.elements.push_back(scopeToAdd);
            this->scopeToAdd->initialize();
            this->addScope = false;
            this->scopeToAdd = nullptr;
        }

        return EngineStatus::Continue;
    }

    EngineStatus GameService::update() {
        std::cout << "GameService: update." << std::endl;

        scopes.elements.back()->update();
        return EngineStatus::Continue;
    }

    EngineStatus GameService::lateUpdate() {
        std::cout << "GameService: lateUpdate." << std::endl;

        /// Check for removing Scope
        if (this->removeScope) {
            this->removeScope = false;
            this->scopes.elements.back()->shutdown();
            this->scopes.elements.back()->resume();
            delete this->scopes.elements.back();
            this->scopes.elements.pop_back();
        }
        return EngineStatus::Continue;
    }
}
