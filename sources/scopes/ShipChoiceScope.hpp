# pragma once

#include "imgui.h"
#include "engine/ForwardDeclaration.hpp"
#include "engine/service/GameService.hpp"
#include "entities/ships/sub/XWing.hpp"


namespace Scopes {

    class ShipChoiceScope : public SCOPE {
    public:
        explicit ShipChoiceScope(GAME_SERVICE *gameService) : SCOPE(gameService) {}
        static int g_Ship;

        ~ShipChoiceScope() = default;


        void initialize() override {
        }

        void pause() override {
        }

        void resume() override {
        }

        void shutdown() override {
        }

        void update() override;
    };
    static void createShip(SCOPE *scope) {
        switch (ShipChoiceScope::g_Ship) {
            case (0):
                scope->entityManager.add<Entities::XWing>(LAYER::Layer1, network::protocol::Update::Master);
                break;
            case (1):
                scope->entityManager.add<Entities::YWing>(LAYER::Layer1, network::protocol::Update::Master);
                break;
            case (2):
                scope->entityManager.add<Entities::_Wing>(LAYER::Layer1, network::protocol::Update::Master);
                break;
            case (3):
                scope->entityManager.add<Entities::Interceptor>(LAYER::Layer1, network::protocol::Update::Master);
                break;
            case (4):
                scope->entityManager.add<Entities::Arc>(LAYER::Layer1, network::protocol::Update::Master);
                break;
            default:
                break;
        }
    }
}

