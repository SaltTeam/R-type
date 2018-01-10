
#pragma once

#include <entities/BaseEntity.hpp>
#include <engine/Manager.hpp>

namespace Services {
    class GameService;
}

namespace Scopes {
    class BaseScope {
    protected:
        Services::GameService *gameService;

    public:
        Manager<Entities::BaseEntity> entityManager;

        explicit BaseScope(Services::GameService *gameService);

        virtual ~BaseScope() = default;

        virtual void initialize() = 0;

        virtual void pause() = 0;

        virtual void resume() = 0;

        virtual void update() = 0;

        virtual void shutdown() = 0;
    };
}
