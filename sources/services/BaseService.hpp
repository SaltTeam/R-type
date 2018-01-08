
#pragma once

#include <string>
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
        virtual void initialize() = 0;

        virtual void earlyUpdate() = 0;

        virtual void update() = 0;

        virtual void lateUpdate() = 0;

        virtual void shutdown() = 0;
    };
}
