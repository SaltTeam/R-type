
#pragma once

#include <cstdint>
#include <utility>
#include <unordered_map>
#include <functional>
#include <SFML/System/Vector2.hpp>
#include <list>

#include "engine/ForwardDeclaration.hpp"
#include "engine/display/Texture.hpp"
#include "server/Protocol.hpp"

namespace Engine {
    namespace Entities {

        class BaseEntity {
            friend ENTITY_MANAGER;
            friend NET_SERVICE;

        protected:
            std::map<int, std::function<void(void)>> callbacks;
            SCOPE *scope;
            network::protocol::Type type;
            network::protocol::Update updateType;
            uint16_t refreshTime;

        public:
            uint64_t id;
            bool isEnabled;
            sf::Vector2f position;
            std::unique_ptr<SFML_TEXTURE> texture;

            explicit BaseEntity(SCOPE *scope, uint64_t id, bool isEnabled = true, float const &x = 0,
                                float const &y = 0)
                    : scope(scope), id(id), isEnabled(isEnabled), position{x, y} {}

            virtual ~BaseEntity() = default;

            void setTexture(std::unique_ptr<SFML_TEXTURE> &texture) {
                this->texture = std::move(texture);
            }

            template<typename... Args>
            void setTexture(Args &&...args) {
                this->texture = std::make_unique<SFML_TEXTURE>(std::forward<Args>(args)...);
            }

            void setPosition(float const &x, float const &y);

            void setPosition(float const &xy);

            void setPosition(sf::Vector2f const &xy);

            void registerCallback(sf::Keyboard::Key key, std::function<void(void)> &f);

            void registerCollisionBox(const sf::FloatRect &size, std::function<void(ENTITY *)> &f);

            void registerCollisionBox(const sf::Vector2f &origin, const sf::FloatRect &size, std::function<void(ENTITY *)> &f);

        protected:
            virtual void update() = 0;
        };

        enum class Layer : unsigned int {
            NotDisplayed = 0,
            Layer1,
            Layer2,
            Layer3,
            Layer4,
            Layer5
        };

        class EntityManager {
            friend GRAPHICAL_SERVICE;
            friend NET_SERVICE;
            friend SCOPE;

        private:
            std::unordered_map<Layer, std::list<ENTITY *>> entities;
            std::list<ENTITY *> removedEntities;

        public:
            ~EntityManager() {
                std::for_each(this->entities.begin(), this->entities.end(),
                              [&](auto &layer) {
                                  std::for_each(layer.second.begin(), layer.second.end(),
                                                [&](auto &entity) -> void { delete entity; });
                              });
            }

            template<typename T, typename... Args>
            void add(Layer layer, Args &&...args) {
                this->entities[layer].push_back(new T(std::forward<Args>(args)...));
            }

            template<typename T>
            T *find(uint64_t id) {
                for (auto &layer: this->entities) {
                    auto ptr = std::find_if(layer.second.begin(), layer.second.end(),
                                            [&, id](const auto &item) -> bool {
                                                if (item->id == id) {
                                                    return dynamic_cast<T *>(item) != nullptr;
                                                }
                                                return false;
                                            });
                    if (ptr != nullptr)
                        return ptr;
                }
                return nullptr;
            }

            void update() {
                // REMOVE WAITING ENTITY
                this->_removeWaitingEntities();
                // UPDATE
                for (auto &layer: this->entities) {
                    for (auto &entity: layer.second) {
                        if (entity->isEnabled) entity->update();
                    }
                }
            }

        private:
            void remove(ENTITY *entity) {
                entity->isEnabled = false;
                this->removedEntities.push_back(entity);
            }

            void _removeWaitingEntities() {
                if (this->removedEntities.empty()) return;
                for (auto &layer: this->entities) {
                    for (auto &entity: layer.second) {
                        for (auto &deleteEntity: this->removedEntities) {
                            if (entity == deleteEntity) {
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
        };

    }
}
