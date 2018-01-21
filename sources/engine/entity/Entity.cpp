
#include "Entity.hpp"
#include "engine/entity/Collision.hpp"
#include "engine/service/GameService.hpp"
#include "engine/scope/Scope.hpp"
#include "engine/Runner.hpp"
#include "engine/service/NetService.hpp"

void ENTITY::registerCallback(sf::Keyboard::Key key, std::function<void(void)> &f) {
    this->scope->registerCallback(key, this, f);
}

void ENTITY::setPosition(float const &x, float const &y) {
    this->position = {x, y};
}

void ENTITY::setPosition(float const &xy) {
    this->position = {xy, xy};
}

void ENTITY::setPosition(sf::Vector2f const &xy) {
    this->position = xy;
}

void ENTITY::registerCollisionBox(const sf::FloatRect &size, std::function<void(ENTITY *)> &f) {
    COLLISION col{f, {0, 0}, size};
    this->scope->collisionManager.registerCollision(this, col);
}

void ENTITY::registerCollisionBox(const sf::Vector2f &origin, const sf::FloatRect &size, std::function<void(ENTITY *)> &f) {
    COLLISION col{f, origin, size};
    this->scope->collisionManager.registerCollision(this, col);
}

uint64_t ENTITY_MANAGER::generateId() {
    static uint64_t lastId = 0;
    for (;;) {
        if (!this->exists(lastId)) {
            return lastId;
        }
        if (lastId > 0x00ffffff)
            lastId = 0;
        lastId++;
    }
}

Engine::Entities::EntityManager::~EntityManager() {
    std::for_each(this->entities.begin(), this->entities.end(),
                  [&](auto &layer) {
                      std::for_each(layer.second.begin(), layer.second.end(),
                                    [&](auto &entity) -> void { delete entity; });
                  });
}


ENTITY *Engine::Entities::EntityManager::find(uint64_t id) {
    for (auto &layer: this->entities) {
        /*auto ptr = std::find_if(layer.second.begin(), layer.second.end(),
                                [&id](const auto &item) -> bool {
                                    return item->id == id;
                                });
        if (*ptr != nullptr)
            return *ptr;*/
        for (auto ptr : layer.second)
        {
            if (ptr->id == id)
                return ptr;

        }
    }
    return nullptr;
}

bool Engine::Entities::EntityManager::exists(uint64_t id) {
    for (auto &layer: this->entities) {
        bool check = false;
        std::for_each(layer.second.begin(), layer.second.end(),
                      [&check, &id](const auto &item) {
                          if (item->id == id) {
                              check = true;
                          }
                      });
        if (check == true)
            return true;
    }
    return false;
}

void Engine::Entities::EntityManager::update() {
    // REMOVE WAITING ENTITY
    this->_removeWaitingEntities();
    // UPDATE
    for (auto &layer: this->entities) {
        for (auto &entity: layer.second) {
            if (entity->isEnabled) entity->update();
        }
    }
}

void Engine::Entities::EntityManager::remove(ENTITY *entity) {
    entity->isEnabled = false;
    this->removedEntities.push_back(entity);
}

void ENTITY_MANAGER::_removeWaitingEntities() {
    if (this->removedEntities.empty()) return;
    for (auto &layer: this->entities) {
        for (auto &entity: layer.second) {
            for (auto &deleteEntity: this->removedEntities) {
                if (entity == deleteEntity) {
                    this->scope->gameService->engine->findService<NET_SERVICE>()->sendEntityDeletion(entity->type, entity->id);
                    delete entity;
                    this->entities[layer.first].remove(entity);
                    this->removedEntities.remove(deleteEntity);
                    this->_removeWaitingEntities(); // Recursive
                    return;
                }
            }
        }
    }
}