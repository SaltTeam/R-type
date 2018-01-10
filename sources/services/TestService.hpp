
#pragma once

#include <iostream>
#include <engine/Engine.hpp>

#include "engine/EngineStop.hpp"
#include "services/BaseService.hpp"

namespace Services {
    class TestService : public Services::BaseService {
    private:
        int end = 0;

    public:
        explicit TestService(Engine *e) : BaseService(e) {
            std::cout << "Test Service: constructor." << std::endl;
        };

        ~TestService() override {
            std::cout << "Test Service: destructor." << std::endl;
        };

        EngineStatus initialize() override {
            std::cout << "Test Service: initialize." << std::endl;
            return EngineStatus::Continue;
        }

        EngineStatus shutdown() override {
            std::cout << "Test Service: shutdown." << std::endl;
            return EngineStatus::Continue;
        }

        EngineStatus earlyUpdate() override {
            std::cout << "Test Service: earlyUpdate." << std::endl;
            return EngineStatus::Continue;
        }

        EngineStatus update() override {
            std::cout << "Test Service: update." << std::endl;
            ++this->end;
            if (this->end >= 0)
                throw CriticalEngineError(EngineErrorReason("Just stop", EngineErrorCode::UNKONWN_UPDATE_FAILED));
            return EngineStatus::Continue;
        }

        EngineStatus lateUpdate() override {
            std::cout << "Test Service: lateUpdate." << std::endl;
            return EngineStatus::Continue;
        }

        void test() {
            std::cout << "Test Service: test." << std::endl;
        }
    };
}
