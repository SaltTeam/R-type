
#include "GameService.hpp"
#include "engine/Runner.hpp"

EngineStatus GAME_SERVICE::initialize() {
    if (this->scopes.empty())
        this->scopes.top()->initialize();
    return EngineStatus::Continue;
}

EngineStatus GAME_SERVICE::shutdown() {
    while (!this->scopes.empty()) {
        this->scopes.top()->shutdown();
        this->scopes.pop();
    }
    return EngineStatus::Continue;
}

EngineStatus GAME_SERVICE::earlyUpdate() {
    /// Check for adding Scope
    if (this->addScope) {
        if (!scopes.empty())
            this->scopes.top()->pause();
        this->scopes.push(this->scopeToAdd);
        this->scopeToAdd->initialize();
        this->addScope = false;
        this->scopeToAdd = nullptr;
    }
    if (scopes.empty())
        return EngineStatus::Stop;
    return EngineStatus::Continue;
}

EngineStatus GAME_SERVICE::update() {
    if (!scopes.empty()) {
        scopes.top()->earlyUpdate();
        scopes.top()->entityManager.update();
        scopes.top()->update();
    }
    return EngineStatus::Continue;
}

EngineStatus GAME_SERVICE::lateUpdate() {
    /// Check for removing Scope
    if (this->removeScope) {
        this->removeScope = false;
        this->scopes.top()->shutdown();
        delete this->scopes.top();
        this->scopes.pop();
    }
    return EngineStatus::Continue;
}

void GAME_SERVICE::execCallbacks() {
    this->scopes.top()->execCallbacks();
}

sf::Vector2u Engine::Services::GameService::getWindowSize() {
    return this->engine->findService<GRAPHICAL_SERVICE>()->getWindowSize();
}
