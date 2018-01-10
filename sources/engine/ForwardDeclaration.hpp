
#pragma once

#include <memory>

namespace Engine {
    class Runner;

    namespace Services {
        class BaseService;
        class ServiceManager;

        class GraphicalService;
        class GameService;
    }

    namespace Entities {
        class BaseEntity;
        class EntityManager;

        enum class Layer : unsigned int;
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

#define ENTITY Engine::Entities::BaseEntity
#define ENTITY_MANAGER Engine::Entities::EntityManager

#define LAYER Engine::Entities::Layer

#define SCOPE Engine::Scopes::BaseScope
#define SCOPE_MANAGER Engine::Scopes::ScopeManager

#define TEXTURE Engine::Display::Texture
#define SFML_TEXTURE Engine::Display::SFMLTexture
