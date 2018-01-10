
#pragma once

#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <exception>

#include "services/BaseService.hpp"
#include "engine/Manager.hpp"
#include "engine/EngineStop.hpp"

#define SERVICE Services::BaseService

class Engine {
public:
    enum class Status {
        Continue = 0,
        Stop = 1
    };

private:
    bool running = false;

    Manager<SERVICE> services;

public:
    Engine() = default;

    ~Engine() = default;

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

        this->execute(this->services, &SERVICE::initialize);
        do {
            this->execute(this->services, &SERVICE::earlyUpdate);
            this->execute(this->services, &SERVICE::update);
            this->execute(this->services, &SERVICE::lateUpdate);
        } while (running);
        this->execute(this->services, &SERVICE::shutdown);
    }

private:
    template<typename T, typename RetType, typename... Args>
    void execute(Manager<T> &manager, RetType (T::*f)(Args...), Args &&...args) {
        try {
            manager.execute<RetType, Args...>(f, args...);
        } catch (CriticalEngineError &e) {
            std::cout << std::hex << std::showbase;
            std::cout << "Critical Error detected: message: " << e.reason.msg << ", code: " << e.reason.code << " ("
                      << (unsigned int) e.reason.code << ")" << std::endl;
            std::cout << std::dec << std::noshowbase;
            running = false;
        };
    }

    template<typename... Args>
    void execute(Manager<SERVICE> &manager, EngineStatus (SERVICE::*f)(Args...), Args &&...args) {
        try {
            std::list<EngineStatus> ret = manager.execute<EngineStatus, Args...>(f, args...);
            std::for_each(ret.begin(), ret.end(), [&](auto &elem) { if (elem == EngineStatus::Stop) running = false; });
        } catch (CriticalEngineError &e) {
            std::cout << std::hex << std::showbase;
            std::cout << "Critical Error detected: message: " << e.reason.msg << ", code: " << e.reason.code << " ("
                      << (unsigned int) e.reason.code << ")" << std::endl;
            std::cout << std::dec << std::noshowbase;
            running = false;
        };
    }
};

#undef SERVICE
