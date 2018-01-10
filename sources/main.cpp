//
// Created by sylva on 08/01/2018.
//

#include <iostream>

#include "engine/Engine.hpp"
#include "scopes/EmptyScope.hpp"
#include "services/TestService.hpp"
#include "services/GameService.hpp"
#include "services/GraphicalService.hpp"

int main() {
    auto e = Engine();

    e.addService<Services::GameService>();
    e.findService<Services::GameService>()->registerBaseScope<Scopes::EmptyScope>();

    e.addService<Services::GraphicalService>();

    e.run();
}
