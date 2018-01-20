
#include "Entity.hpp"

#include "engine/entity/Collision.hpp"
#include "engine/service/GameService.hpp"

void ENTITY::registerCallback(sf::Keyboard::Key key, std::function<void(void)> &f) {
    this->scope->registerCallback(key, this, f);
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

void ENTITY::registerCollisionBox(const sf::FloatRect &size, std::function<void(ENTITY *)> &f) {
    COLLISION col{f, {0, 0}, size};
    this->scope->collisionManager.registerCollision(this, col);
}

void ENTITY::registerCollisionBox(const sf::Vector2f &origin, const sf::FloatRect &size, std::function<void(ENTITY *)> &f) {
    COLLISION col{f, origin, size};
    this->scope->collisionManager.registerCollision(this, col);
}

uint64_t ENTITY_MANAGER::generateId() {
    static uint64_t lastId = 0;
    for (;;) {
        if (!this->exists(lastId)) {
            return lastId;
        }
        if (lastId > 0x00ffffff)
            lastId = 0;
        lastId++;
    }
}
