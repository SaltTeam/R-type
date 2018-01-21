//
// Created by delacr_a on 21/01/18.
//

#include "star.hpp"
#include "engine/service/GameService.hpp"

Entities::Star::Star(SCOPE *scope, uint64_t id, network::protocol::PlayerColor playerColor)
        : MovableEntity(scope, id, playerColor, network::protocol::Update::Instanciated, 250, true, 0, 0)
{
    this->setTexture("resources/sprites/starfield/star.png");

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist_xpos(-(this->texture->sprite.getGlobalBounds().width / 2),
                                                    this->scope->gameService->getWindowSize().x - (this->texture->sprite.getGlobalBounds().width / 2));
    std::uniform_real_distribution<float> dist_speed(0.01f, 0.1f);

    float speed = dist_speed(mt);
    sf::Uint8 light = 255 * (speed * 10);
    this->texture->sprite.setColor(sf::Color(light, light, light));
    this->setSpeed(0, speed);
    this->setPosition(dist_xpos(mt), -this->texture->sprite.getGlobalBounds().height * (1 / speed));
}

void Entities::Star::update() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist_xpos(-(this->texture->sprite.getGlobalBounds().width / 2),
                                                    this->scope->gameService->getWindowSize().x - (this->texture->sprite.getGlobalBounds().width / 2));

    this->move();
    sf::Vector2u borders = this->scope->gameService->getWindowSize();
    if (this->position.y > borders.y)
        this->setPosition(dist_xpos(mt), -this->texture->sprite.getGlobalBounds().height);
}

