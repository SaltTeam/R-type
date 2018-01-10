
#include "NetService.hpp"

namespace Engine {
    EngineStatus Services::NetService::initialize() {
        return EngineStatus::Continue;
    }

    EngineStatus Services::NetService::earlyUpdate() {
        return EngineStatus::Continue;
    }

    EngineStatus Services::NetService::update() {
        return EngineStatus::Continue;
    }

    EngineStatus Services::NetService::lateUpdate() {
        return EngineStatus::Continue;
    }

    EngineStatus Services::NetService::shutdown() {
        return EngineStatus::Continue;
    }
}