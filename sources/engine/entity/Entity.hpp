
#pragma once

#include <cstdint>
#include <utility>
#include <unordered_map>
#include <functional>
#include <SFML/System/Vector2.hpp>

#include "engine/ForwardDeclaration.hpp"
#include "engine/display/Texture.hpp"

namespace Engine {
    namespace Entities {

        class BaseEntity {
            friend ENTITY_MANAGER;
        protected:
            std::map<int, std::function<void(void)>> callbacks;
            SCOPE *scope;

        public:
            uint64_t id;
            bool isEnabled;
            sf::Vector2f position;
            std::unique_ptr<SFML_TEXTURE> texture;

            explicit BaseEntity(SCOPE *scope, uint64_t id, bool isEnabled = true)
                    : scope(scope), id(id), isEnabled(isEnabled), position{0, 0} {}

            virtual ~BaseEntity() = default;

            void setTexture(std::unique_ptr<SFML_TEXTURE> &texture) {
                this->texture = std::move(texture);
            }

            template<typename... Args>
            void setTexture(Args&&...args) {
                this->texture = std::make_unique<SFML_TEXTURE>(std::forward<Args>(args)...);
            }

            void registerCallback(sf::Keyboard::Key key, std::function<void(void)> &f);

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

        private:
            std::unordered_map<Layer, std::vector<ENTITY *>> entities;

        public:
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
                for (auto &layer: this->entities) {
                    for (auto &entity: layer.second) {
                        entity->update();
                    }
                }
            }
        };

    }
}
