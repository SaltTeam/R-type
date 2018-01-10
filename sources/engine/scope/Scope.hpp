
#pragma once

#include <memory>

#include "engine/ForwardDeclaration.hpp"
#include "engine/entity/Entity.hpp"

namespace Engine {
    namespace Scopes {

        class BaseScope {
        protected:
            GAME_SERVICE *gameService;

        public:
            ENTITY_MANAGER entityManager;

            explicit BaseScope(GAME_SERVICE *gameService) : gameService(gameService) {}

            virtual ~BaseScope() = default;

            virtual void initialize() = 0;

            virtual void pause() = 0;

            virtual void resume() = 0;

            virtual void update() = 0;

            virtual void shutdown() = 0;
        };

    }
}
