
#pragma once

#include <list>
#include <algorithm>
#include <memory>
#include <future>

#include "engine/ForwardDeclaration.hpp"
#include "engine/EngineStatus.hpp"

namespace Engine {
    namespace Services {

        class BaseService {
            friend ENGINE;
            friend SERVICE_MANAGER;

        public:
            ENGINE *engine;

        protected:
            explicit BaseService(ENGINE *engine) : engine(engine) {}

            virtual ~BaseService() = default;

        private:
            virtual EngineStatus initialize() = 0;

            virtual EngineStatus earlyUpdate() = 0;

            virtual EngineStatus update() = 0;

            virtual EngineStatus lateUpdate() = 0;

            virtual EngineStatus shutdown() = 0;
        };

        class ServiceManager {
            friend ENGINE;

        private:
            std::list<SERVICE *> services;

            ServiceManager() = default;

            virtual ~ServiceManager() {
                std::for_each(this->services.begin(), this->services.end(), [&](auto &elem) { delete elem; });
            }

            template<typename RetType, typename... Args>
            std::list<RetType> execute(RetType (SERVICE::*f)(Args...), Args &...args) {
                std::list<RetType> ret;
                std::for_each(this->services.begin(), this->services.end(),
                              [&, args...](auto &elem) -> void {
                                  ret.push_back((elem->*f)(args...));
                              });
                return ret;
            };

            template<typename... Args>
            void execute(void (SERVICE::*f)(Args...), Args &...args) {
                std::for_each(this->services.begin(), this->services.end(),
                              [&, args...](auto &elem) -> void {
                                  (elem->*f)(args...);
                              });
            };

            template<typename U>
            U *find() {
                auto elem = std::find_if(this->services.begin(), this->services.end(),
                                         [&](const auto &elem) -> bool {
                                             return dynamic_cast<U *>(elem) != nullptr;
                                         });
                if (elem == this->services.end()) return nullptr;
                else return dynamic_cast<U *>((*elem));
            }

            template<typename U, typename... Args>
            U *add(Args...args) {
                U *elem = this->find<U>();
                if (elem == nullptr) {
                    elem = new U(args...);
                    this->services.push_back(elem);
                }
                return elem;
            }

            template<typename U>
            void remove() {
                U *elem = this->find<U>();
                if (elem != nullptr) {
                    delete elem;
                    this->services.remove(elem);
                }
            }

        };

    }
}
