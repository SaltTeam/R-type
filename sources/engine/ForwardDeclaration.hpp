
#pragma once

#include <memory>

namespace Engine {
    class Runner;

    namespace Services {
        class BaseService;
        class ServiceManager;

        class GraphicalService;
        class GameService;
        class NetService;
    }

    namespace Entities {
        class BaseEntity;
        class EntityManager;

        enum class Layer : unsigned int;

        struct Collision;
        class CollisionManager;
    }

    namespace Scopes {
        class BaseScope;
        class ScopeManager; // TODO
    }

    namespace Display {
        class Texture;
    }
}

#define ENGINE Engine::Runner

#define SERVICE Engine::Services::BaseService
#define SERVICE_MANAGER Engine::Services::ServiceManager
#define GRAPHICAL_SERVICE Engine::Services::GraphicalService
#define GAME_SERVICE Engine::Services::GameService
#define NET_SERVICE Engine::Services::NetService

#define ENTITY Engine::Entities::BaseEntity
#define MOVABLE_ENTITY Engine::Entities::MovableEntity
#define ENTITY_MANAGER Engine::Entities::EntityManager
#define COLLISION Engine::Entities::Collision
#define COLLISION_MANAGER Engine::Entities::CollisionManager

#define LAYER Engine::Entities::Layer

#define SCOPE Engine::Scopes::BaseScope
#define SCOPE_MANAGER Engine::Scopes::ScopeManager

#define TEXTURE Engine::Display::Texture
#define SFML_TEXTURE Engine::Display::SFMLTexture
