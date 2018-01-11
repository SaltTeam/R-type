
#include "Entity.hpp"

#include "engine/service/GameService.hpp"

void ENTITY::registerCallback(sf::Keyboard::Key key, std::function<void(void)> &f) {
    this->scope->registerCallback(key, f);
}

void ENTITY::setPosition(float const &x, float const &y) {
    this->position = {x, y};
}

void ENTITY::setPosition(float const &xy) {
    this->position = {xy, xy};
}

void ENTITY::setPosition(sf::Vector2f const &xy) {
    this->position = xy;
}
