
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
    }

    namespace Scopes {
        class BaseScope;
        class ScopeManager;
    }
}

#define ENGINE Engine::Runner

#define SERVICE Engine::Services::BaseService
#define SERVICE_MANAGER Engine::Services::ServiceManager
#define GRAPHICAL_SERVICE Engine::Services::GraphicalService
#define GAME_SERVICE Engine::Services::GameService

#define ENTITY Engine::Entities::BaseEntity
#define ENTITY_MANAGER Engine::Entities::EntityManager

#define SCOPE Engine::Scopes::BaseScope
#define SCOPE_MANAGER Engine::Scopes::ScopeManager
