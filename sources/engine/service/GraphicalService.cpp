
#include "engine/ForwardDeclaration.hpp"
#include "GraphicalService.hpp"
#include "engine/Runner.hpp"
#include "engine/service/GameService.hpp"
#include "engine/scope/Scope.hpp"

EngineStatus GRAPHICAL_SERVICE::initialize() {
    this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode(720, 980), "R-type");
    return EngineStatus::Continue;
}

EngineStatus GRAPHICAL_SERVICE::earlyUpdate() {
    sf::Event event{};
    while (this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            this->window->close();
            return EngineStatus::Stop;
        }
    }
    this->engine->findService<GAME_SERVICE>()->execCallbacks();
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
