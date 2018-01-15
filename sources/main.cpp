
#include <iostream>

#include "engine/Runner.hpp"
#include "services/TestService.hpp"
#include "engine/service/NetService.hpp"
#include "engine/service/GameService.hpp"
#include "engine/service/GraphicalService.hpp"
#include "scopes/TestScope.hpp"

int main() {
    auto e = ENGINE();

    e.addService<GAME_SERVICE>();
    e.findService<GAME_SERVICE>()->registerBaseScope<Scopes::TestScope>();
    e.addService<GRAPHICAL_SERVICE>();

    e.run();
}
