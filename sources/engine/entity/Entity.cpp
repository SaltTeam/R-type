
#include "Entity.hpp"

#include "engine/service/GameService.hpp"

void ENTITY::registerCallback(sf::Keyboard::Key key, std::function<void(void)> &f) {
    this->scope->registerCallback(key, f);
}
