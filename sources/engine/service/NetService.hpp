
#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include "server/Protocol.hpp"
#include "engine/service/Service.hpp"

namespace Engine {
    namespace Services {
        class NetService : public SERVICE {
            friend ENGINE;
            friend SERVICE_MANAGER;

        private:
            std::thread *thread;
            std::atomic_bool running;
            std::queue<network::protocol::ObjectHeader *> in;
            std::queue<network::protocol::ObjectHeader *> out;
            std::mutex mut_in;
            std::mutex mut_out;

        public:
            explicit NetService(ENGINE *engine) : SERVICE(engine), mut_in(), mut_out() {}

            ~NetService() override = default;

            void run();

        private:
            EngineStatus initialize() override;

            EngineStatus earlyUpdate() override;

            EngineStatus update() override;

            EngineStatus lateUpdate() override;

            EngineStatus shutdown() override;
        };
    }
}