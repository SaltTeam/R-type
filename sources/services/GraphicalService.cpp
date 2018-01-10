
#include "GraphicalService.hpp"

#include "engine/EngineStop.hpp"

Services::GraphicalService::GraphicalService(Engine *engine) : BaseService(engine) {}

EngineStatus Services::GraphicalService::initialize() {
    this->window = std::make_unique<sf::Window>(sf::VideoMode(800, 600), "R-type");
    return EngineStatus::Continue;
}

EngineStatus Services::GraphicalService::earlyUpdate() {
    sf::Event event{};
    while (this->window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->window->close();
            return EngineStatus::Stop;
        }
    }
    return EngineStatus::Continue;
}

EngineStatus Services::GraphicalService::update() {
    return EngineStatus::Continue;
}

EngineStatus Services::GraphicalService::lateUpdate() {
    this->window->display();
    return EngineStatus::Continue;
}

EngineStatus Services::GraphicalService::shutdown() {
    return EngineStatus::Continue;
}
