
#include "BaseScope.hpp"

#include "services/GameService.hpp"

namespace Scopes {
    BaseScope::BaseScope(Services::GameService *gameService) : gameService(gameService) {}
}
