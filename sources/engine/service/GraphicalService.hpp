
#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "engine/service/Service.hpp"

namespace Engine {
    namespace Services {
        class GraphicalService : public SERVICE {
            friend ENGINE;
            friend SERVICE_MANAGER;

        private:
            std::unique_ptr<sf::RenderWindow> window = nullptr;
            sf::Clock deltaClock;
            sf::Clock clock;
            sf::Time currentTime;
            sf::Time frameTime;
            bool render;

        public:
            static sf::Time ups;
            static sf::Time deltaTime;

            explicit GraphicalService(ENGINE *engine) : SERVICE(engine) {}

            ~GraphicalService() override = default;

            sf::Vector2u getWindowSize() {
                return this->window->getSize();
            };

        private:
            EngineStatus initialize() override;

            EngineStatus earlyUpdate() override;

            EngineStatus update() override;

            EngineStatus lateUpdate() override;

            EngineStatus shutdown() override;
        };
    }
}