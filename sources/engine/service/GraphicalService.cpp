
#include <imgui-SFML.h>
#include "engine/ForwardDeclaration.hpp"
#include "GraphicalService.hpp"
#include "engine/Runner.hpp"
#include "engine/service/GameService.hpp"
#include "engine/scope/Scope.hpp"

EngineStatus GRAPHICAL_SERVICE::initialize() {
    this->window = std::make_unique<sf::RenderWindow>(sf::VideoMode(720, 980), "R-type");
    this->window->setFramerateLimit(120);
    ImGui::SFML::Init(*this->window);
    return EngineStatus::Continue;
}

EngineStatus GRAPHICAL_SERVICE::earlyUpdate() {
    sf::Event event{};
    while (this->window->pollEvent(event)) {
        ImGui::SFML::ProcessEvent(event);

        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            this->window->close();
            ImGui::SFML::Update(*this->window, this->deltaClock.restart());
            return EngineStatus::Stop;
        }
    }
    ImGui::SFML::Update(*this->window, this->deltaClock.restart());
    this->engine->findService<GAME_SERVICE>()->execCallbacks();
    return EngineStatus::Continue;
}

EngineStatus GRAPHICAL_SERVICE::update() {
    return EngineStatus::Continue;
}

EngineStatus GRAPHICAL_SERVICE::lateUpdate() {
    GAME_SERVICE *game = this->engine->findService<GAME_SERVICE>();
    SCOPE *scope = game->currentScope();
    if (scope == nullptr)
        return EngineStatus::Stop;
    this->window->clear();
    for (const auto &layer : scope->entityManager.entities) {
        for (const auto &entity : layer.second) {
            if (entity->texture) {
                entity->texture->sprite.setPosition(entity->position);
                this->window->draw(entity->texture->sprite);
            }
        }
    }
    ImGui::SFML::Render(*this->window);
    this->window->display();
    return EngineStatus::Continue;
}

EngineStatus GRAPHICAL_SERVICE::shutdown() {
    ImGui::SFML::Shutdown();
    if (this->window->isOpen())
        this->window->close();
    return EngineStatus::Continue;
}
