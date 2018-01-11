
#pragma once

#include <memory>
#include <list>

#include "engine/ForwardDeclaration.hpp"
#include "engine/entity/Entity.hpp"

namespace Engine {
    namespace Scopes {

        class BaseScope {
        private:
            std::map<sf::Keyboard::Key, std::list<std::function<void(void)>>> callbacks;

        public:
            GAME_SERVICE *gameService;

            ENTITY_MANAGER entityManager;

            explicit BaseScope(GAME_SERVICE *gameService) : gameService(gameService) {}

            virtual ~BaseScope() = default;

            virtual void initialize() = 0;

            virtual void pause() = 0;

            virtual void resume() = 0;

            virtual void update() = 0;

            void execCallbacks();

            virtual void shutdown() = 0;

            void registerCallback(sf::Keyboard::Key key, std::function<void(void)> &f);
        };

    }
}
