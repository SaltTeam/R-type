
#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <atomic>
#include "server/Protocol.hpp"
#include "engine/service/Service.hpp"
#include "network/Socket.hpp"
#include "network/SocketException.hpp"

namespace Engine {
    namespace Services {
        class NetService : public SERVICE {
            friend ENGINE;
            friend SERVICE_MANAGER;

        private:
            std::thread *thread;
            std::atomic_bool running;
            std::atomic_bool connect;
            std::queue<network::protocol::ObjectHeader *> in;
            std::queue<network::protocol::ObjectHeader *> out;
            std::mutex mut_in;
            std::mutex mut_out;
            unsigned short port;
            std::string address;

        public:
            static network::protocol::PlayerColor color;

            explicit NetService(ENGINE *engine) : SERVICE(engine), mut_in(), mut_out() {}

            ~NetService() override = default;

            void run();

            void runRead();

            network::protocol::Status connectTCP(std::string const& name,
                                                 std::string const& passwd,
                                                 std::string const& ipAddr);

            void sendEntityDeletion(network::protocol::Type type, uint64_t id);

        private:
            EngineStatus initialize() override;

            EngineStatus earlyUpdate() override;

            EngineStatus update() override;

            EngineStatus lateUpdate() override;

            EngineStatus shutdown() override;
        };
    }
}