
#include "engine/ForwardDeclaration.hpp"
#include "GraphicalService.hpp"
#include "engine/Runner.hpp"
#include "engine/service/GameService.hpp"
#include "engine/scope/Scope.hpp"

EngineStatus GRAPHICAL_SERVICE::initialize() {
    this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "R-type");
    return EngineStatus::Continue;
}

EngineStatus GRAPHICAL_SERVICE::earlyUpdate() {
    sf::Event event{};
    while (this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->window->close();
            return EngineStatus::Stop;
        } else if (event.type == sf::Event::KeyPressed) {
            this->engine->findService<GAME_SERVICE>()->execCallbacks(event.key.code);
        }
    }
    return EngineStatus::Continue;
}

EngineStatus GRAPHICAL_SERVICE::update() {
    return EngineStatus::Continue;
}

EngineStatus GRAPHICAL_SERVICE::lateUpdate() {
    GAME_SERVICE *game = this->engine->findService<GAME_SERVICE>();
    SCOPE *scope = game->currentScope();
    this->window->clear();
    for (const auto &layer : scope->entityManager.entities) {
        for (const auto &entity : layer.second) {
            if (entity->texture) {
                entity->texture->sprite.setPosition(entity->position);
                this->window->draw(entity->texture->sprite);
            }
        }
    }
    this->window->display();
    return EngineStatus::Continue;
}

EngineStatus GRAPHICAL_SERVICE::shutdown() {
    if (this->window->isOpen())
        this->window->close();
    return EngineStatus::Continue;
}
