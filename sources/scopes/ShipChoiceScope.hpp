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

        static void createShip(SCOPE *scope);
    };
}

