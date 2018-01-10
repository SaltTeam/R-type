
#pragma once

#include <string>

#include "engine/EngineStatus.hpp"
#include "engine/Manager.hpp"

class Engine;

namespace Services {
    class BaseService {
        friend Engine;
        friend Manager<Services::BaseService>;

    protected:
        Engine *engine;

        explicit BaseService(Engine *engine);

        virtual ~BaseService() = default;

    private:
        virtual EngineStatus initialize() = 0;

        virtual EngineStatus earlyUpdate() = 0;

        virtual EngineStatus update() = 0;

        virtual EngineStatus lateUpdate() = 0;

        virtual EngineStatus shutdown() = 0;
    };
}
