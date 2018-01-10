
#pragma once

#include "engine/service/Service.hpp"

namespace Engine {
    namespace Services {
        class NetService : public SERVICE {
            friend ENGINE;
            friend SERVICE_MANAGER;

        public:
            explicit NetService(ENGINE *engine) : SERVICE(engine) {}

            ~NetService() override = default;

        private:
            EngineStatus initialize() override;

            EngineStatus earlyUpdate() override;

            EngineStatus update() override;

            EngineStatus lateUpdate() override;

            EngineStatus shutdown() override;
        };
    }
}