
#pragma once

#include <cstdint>
#include <utility>
#include <unordered_map>
#include <functional>
#include <SFML/System/Vector2.hpp>
#include <list>
#include <map>
#include <engine/service/NetService.hpp>
#include "engine/display/Texture.hpp"
#include "engine/ForwardDeclaration.hpp"
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
            network::protocol::PlayerColor playerColor;

            explicit BaseEntity(SCOPE *scope, uint64_t id, network::protocol::PlayerColor playerColor,
                                network::protocol::Update updateType, uint16_t refreshTime,
                                bool isEnabled = true, float const &x = 0, float const &y = 0)
                    : scope(scope), id(id), playerColor(playerColor), isEnabled(isEnabled), position{x, y},
                      updateType(updateType), refreshTime(refreshTime) {}

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

            void registerCollisionBox(const sf::Vector2f &origin, const sf::FloatRect &size,
                                      std::function<void(ENTITY *)> &f);

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
            std::list<ENTITY *> removedEntities;
            SCOPE *scope;

        public:
            std::unordered_map<Layer, std::list<ENTITY *>> entities;

            ~EntityManager();

            explicit EntityManager(SCOPE *scope) : scope(scope) {}

            uint64_t generateId();

            template<typename T, typename... Args>
            void add(Layer layer, Args &&...args){
                this->entities[layer].push_back(new T(this->scope, generateId(), NET_SERVICE::color, std::forward<Args>(args)...));
            }

            template<typename T, typename... Args>
            void netAdd(Layer layer, network::protocol::PlayerColor color, Args &&...args){
                this->entities[layer].push_back(new T(this->scope, generateId(), color, std::forward<Args>(args)...));
            }

            template<typename T, typename... Args>
            void netAdd(Layer layer, network::protocol::PlayerColor color, uint64_t id, Args &&...args) {
                this->entities[layer].push_back(new T(this->scope, id, color, std::forward<Args>(args)...));
            }

            ENTITY *find(uint64_t id);

            bool exists(uint64_t id);

            void update();

        private:
            void remove(ENTITY *entity);

            void _removeWaitingEntities();
        };

    }
}
