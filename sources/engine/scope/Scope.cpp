
#include "Scope.hpp"

void SCOPE::registerCallback(sf::Keyboard::Key key, ENTITY *entity, std::function<void(void)> &f) {
    this->callbacks[key][entity].push_back(f);
}

void SCOPE::execCallbacks() {
    for (const auto &registered : this->callbacks) {
        if (sf::Keyboard::isKeyPressed(registered.first)) {
            for (auto &entity : registered.second) {
                for (auto &callback : entity.second) {
                    callback();
                }
            }
        }
    }
}

void SCOPE::earlyUpdate() {
    for (const auto &entity: this->removeList) {
        {
            auto erase = this->collisionManager.collisions.find(entity);
            if (erase != this->collisionManager.collisions.end())
                this->collisionManager.collisions.erase(erase);
        }
        for (auto &elem: this->callbacks) {
            auto erase = elem.second.find(entity);
            if (erase != elem.second.end())
                elem.second.erase(erase);
        }
    }
    this->removeList.clear();
}

void SCOPE::removeEntity(ENTITY *entity) {
    this->removeList.push_back(entity);
    this->entityManager.remove(entity);
}