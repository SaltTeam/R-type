
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
    return this->generateId(network::protocol::PlayerColor::Blue);
}

uint64_t ENTITY_MANAGER::generateId(network::protocol::PlayerColor color) {
    static uint64_t lastId = 0;
    uint64_t headerId;
    switch (color) {
        case network::protocol::PlayerColor::Blue:
            headerId = 0x00000000;
            break;
        case network::protocol::PlayerColor::Green:
            headerId = 0x01000000;
            break;
        case network::protocol::PlayerColor::Red:
            headerId = 0x02000000;
            break;
        case network::protocol::PlayerColor::Yellow:
        default:
            headerId = 0x03000000;
            break;
    }
    for (;;) {
        if (!this->exists(headerId + lastId)) {
            std::cout << headerId + lastId << std::endl;
            return headerId + lastId;
        }
        if (lastId > 0x00ffffff)
            lastId = 0;
        lastId++;
    }
}
