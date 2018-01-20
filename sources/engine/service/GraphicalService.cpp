
#include "engine/ForwardDeclaration.hpp"
#include "GraphicalService.hpp"
#include "engine/Runner.hpp"
#include "engine/service/GameService.hpp"
#include "engine/scope/Scope.hpp"

sf::Time GRAPHICAL_SERVICE::ups = sf::seconds(1.f / 60.f);
sf::Time GRAPHICAL_SERVICE::deltaTime = GRAPHICAL_SERVICE::ups;

EngineStatus GRAPHICAL_SERVICE::initialize() {
    this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode(720, 980), "R-type");
    this->currentTime = this->clock.getElapsedTime();
    this->render = false;
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

    sf::sleep(sf::microseconds(1));

    if (this->frameTime.asSeconds() <= 0) {
        this->render = true;
        sf::Time newTime = this->clock.getElapsedTime();
        this->frameTime = newTime - this->currentTime;
        this->currentTime = newTime;
    }

    this->deltaTime = sf::seconds(std::fmin(this->frameTime.asSeconds(), this->ups.asSeconds()));

    return EngineStatus::Continue;
}

EngineStatus GRAPHICAL_SERVICE::update() {
    return EngineStatus::Continue;
}

EngineStatus GRAPHICAL_SERVICE::lateUpdate() {
    this->frameTime -= this->deltaTime;
    if (this->render) {
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

        this->render = false;
    }
    return EngineStatus::Continue;
}

EngineStatus GRAPHICAL_SERVICE::shutdown() {
    if (this->window->isOpen())
        this->window->close();
    return EngineStatus::Continue;
}
