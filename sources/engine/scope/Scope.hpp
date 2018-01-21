
#pragma once

#include <memory>
#include <list>

#include "engine/ForwardDeclaration.hpp"
#include "engine/entity/Entity.hpp"
#include "engine/entity/Collision.hpp"
#include "entities/starfield/star.hpp"

namespace Engine {
    namespace Scopes {

        class BaseScope {
        private:
            std::map<sf::Keyboard::Key, std::map<ENTITY *, std::list<std::function<void(void)>>>> callbacks;
            std::list<ENTITY *> removeList;

        public:
            GAME_SERVICE *gameService;

            ENTITY_MANAGER entityManager;

            COLLISION_MANAGER collisionManager;

            explicit BaseScope(GAME_SERVICE *gameService) : gameService(gameService), entityManager(this) {}

            virtual ~BaseScope() = default;

            virtual void initialize() = 0;

            virtual void pause() = 0;

            virtual void resume() = 0;

            void earlyUpdate();

            virtual void update() = 0;

            void execCallbacks();

            virtual void shutdown() = 0;

            void registerCallback(sf::Keyboard::Key key, ENTITY *entity, std::function<void(void)> &f);

            void removeEntity(ENTITY *entity);
        };

    }
}

static void createStarfield(SCOPE *scope, int nbr) {
    for (int i = 0; i < nbr; ++i) {
        scope->entityManager.add<Entities::Star>(LAYER::Layer1);
    }
}