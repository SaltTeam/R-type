
#pragma once

#include <list>
#include <algorithm>
#include <memory>
#include <future>
#include "EngineStatus.hpp"

template<typename T>
class Manager {
public:
    std::list<T *> elements;

    Manager() = default;

    virtual ~Manager() {
        std::for_each(this->elements.begin(), this->elements.end(), [&](auto &elem) { delete elem; });
    }

    template<typename RetType, typename... Args>
    std::list<RetType> execute(RetType (T::*f)(Args...), Args &...args) {
        std::list<RetType> ret;
        std::for_each(this->elements.begin(), this->elements.end(),
                      [&, args...](auto &elem) -> void {
                          ret.push_back((elem->*f)(args...));
                      });
        return ret;
    };

    template<typename... Args>
    void execute(void (T::*f)(Args...), Args &...args) {
        std::for_each(this->elements.begin(), this->elements.end(),
                      [&, args...](auto &elem) -> void {
                          (elem->*f)(args...);
                      });
    };

    template<typename U>
    U *find() {
        auto elem = std::find_if(this->elements.begin(), this->elements.end(),
                                 [&](const auto &elem) -> bool {
                                     return dynamic_cast<U *>(elem) != nullptr;
                                 });
        if (elem == this->elements.end()) return nullptr;
        else return dynamic_cast<U *>((*elem));
    }

    template<typename U, typename V>
    U *add(V *arg) {
        U *elem = new U(arg);
        this->elements.push_back(elem);
        return elem;
    }

    template<typename U>
    void remove() {
        U *elem = this->find<U>();
        if (elem != nullptr) {
            delete elem;
            this->elements.remove(elem);
        }
    }
};
