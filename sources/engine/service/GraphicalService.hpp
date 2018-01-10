
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
            std::unique_ptr<sf::Window> window = nullptr;

        public:
            explicit GraphicalService(ENGINE *engine) : SERVICE(engine) {}

            ~GraphicalService() override = default;

        private:
            EngineStatus initialize() override;

            EngineStatus earlyUpdate() override;

            EngineStatus update() override;

            EngineStatus lateUpdate() override;

            EngineStatus shutdown() override;
        };
    }
}