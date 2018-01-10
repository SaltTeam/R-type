
#include "engine/ForwardDeclaration.hpp"
#include "GraphicalService.hpp"

EngineStatus GRAPHICAL_SERVICE::initialize() {
    this->window = std::make_unique<sf::Window>(sf::VideoMode(800, 600), "R-type");
    return EngineStatus::Continue;
}

EngineStatus GRAPHICAL_SERVICE::earlyUpdate() {
    sf::Event event{};
    while (this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->window->close();
            return EngineStatus::Stop;
        }
    }
    return EngineStatus::Continue;
}

EngineStatus GRAPHICAL_SERVICE::update() {
    return EngineStatus::Continue;
}

EngineStatus GRAPHICAL_SERVICE::lateUpdate() {
    this->window->display();
    return EngineStatus::Continue;
}

EngineStatus GRAPHICAL_SERVICE::shutdown() {
    if (this->window->isOpen())
        this->window->close();
    return EngineStatus::Continue;
}
