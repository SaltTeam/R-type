
#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "BaseService.hpp"

namespace Services {
    class GraphicalService : public Services::BaseService {
        friend Engine;
        friend Manager<Services::BaseService>;

    private:
        std::unique_ptr<sf::Window> window = nullptr;

    public:
        explicit GraphicalService(Engine *engine);

        ~GraphicalService() override {}

    private:
        EngineStatus initialize() override;

        EngineStatus earlyUpdate() override;

        EngineStatus update() override;

        EngineStatus lateUpdate() override;

        EngineStatus shutdown() override;
    };
}
