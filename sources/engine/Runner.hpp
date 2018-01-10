
#pragma once

#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <exception>

#include "ForwardDeclaration.hpp"
#include "engine/service/Service.hpp"
#include "engine/EngineStop.hpp"

namespace Engine {

    class Runner {
    private:
        bool running = false;

        SERVICE_MANAGER services;

    public:
        Runner() = default;

        ~Runner() = default;

        template<typename T>
        void addService() {
            this->services.add<T>(this);
        }

        template<typename T>
        T *findService() {
            return this->services.find<T>();
        }

        template<typename T>
        void removeService() {
            this->services.remove<T>();
        };

        void run() {
            this->running = true;

            this->execute(&SERVICE::initialize);
            do {
                this->execute(&SERVICE::earlyUpdate);
                this->execute(&SERVICE::update);
                this->execute(&SERVICE::lateUpdate);
            } while (running);
            this->execute(&SERVICE::shutdown);
        }

    private:
        template<typename RetType, typename... Args>
        void execute(RetType (SERVICE::*f)(Args...), Args &&...args) {
            try {
                this->services.execute<RetType, Args...>(f, args...);
            } catch (CriticalEngineError &e) {
                std::cout << std::hex << std::showbase;
                std::cout << "Critical Error detected: message: " << e.reason.msg << ", code: " << e.reason.code << " ("
                          << (unsigned int) e.reason.code << ")" << std::endl;
                std::cout << std::dec << std::noshowbase;
                running = false;
            };
        }

        template<typename... Args>
        void execute(EngineStatus (SERVICE::*f)(Args...), Args &&...args) {
            try {
                std::list<EngineStatus> ret = this->services.execute<EngineStatus, Args...>(f, args...);
                std::for_each(ret.begin(), ret.end(),
                              [&](auto &elem) { if (elem == EngineStatus::Stop) running = false; });
            } catch (CriticalEngineError &e) {
                std::cout << std::hex << std::showbase;
                std::cout << "Critical Error detected: message: " << e.reason.msg << ", code: " << e.reason.code << " ("
                          << (unsigned int) e.reason.code << ")" << std::endl;
                std::cout << std::dec << std::noshowbase;
                running = false;
            };
        }
    };

}

