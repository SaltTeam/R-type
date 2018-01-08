
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

        void initialize() override {
            std::cout << "Test Service: initialize." << std::endl;
        }

        void shutdown() override {
            std::cout << "Test Service: shutdown." << std::endl;
        }

        void earlyUpdate() override {
            std::cout << "Test Service: earlyUpdate." << std::endl;
        }

        void update() override {
            std::cout << "Test Service: update." << std::endl;
            ++this->end;
            if (this->end >= 0)
                throw CriticalEngineError(EngineErrorReason("Just stop", EngineErrorCode::UNKONWN));
        }

        void lateUpdate() override {
            std::cout << "Test Service: lateUpdate." << std::endl;
        }

        void test() {
            std::cout << "Test Service: test." << std::endl;
        }
    };
}
