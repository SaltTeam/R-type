//
// Created by delacr_a on 17/01/18.
//

#include "entities/powerups/sub/SpeedPowerUp.hpp"
#include "entities/powerups/sub/HealPowerUp.hpp"
#include "entities/powerups/sub/ShieldPowerUp.hpp"
#include "entities/powerups/sub/DamagePowerUp.hpp"
#include "Ship.hpp"

Entities::Ship::Ship(SCOPE *scope, uint64_t id, network::protocol::PlayerColor playerColor,
                     network::protocol::Update updateType, uint16_t refreshTime,
                     bool isEnabled, Entities::Ship::TEAM team, float const &x, float const &y, float const &xSpeed,
                     float const &ySpeed, int const &health, const int &shield)
        : MovableEntity(scope, id, playerColor, updateType, refreshTime, isEnabled, x, y, xSpeed, ySpeed),
          health(health), maxHealth(health), shield(shield), team(team) {
}

Entities::Ship::~Ship() {
    delete weapon;
    if (team == GAME && playerColor == network::protocol::PlayerColor::Blue)
        spawnPowerUp();
}

void Entities::Ship::registerTexture(std::string const &path) {
    this->setTexture(path);
    std::function<void(ENTITY *)> f5 = std::bind(&Ship::onCollision, this, std::placeholders::_1);
    this->registerCollisionBox(this->texture->sprite.getGlobalBounds(), f5);
}

void Entities::Ship::spawnPowerUp() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist_powerup(0, 100);

    int res = dist_powerup(mt);
    if (res < 10)
        this->scope->entityManager.add<Entities::SpeedPowerUp>(LAYER::Layer1,
                                                               static_cast<GRADE>(res % 3), position.x +
                                                                                            this->texture->sprite.getGlobalBounds().width /
                                                                                            2, position.y +
                                                                                               this->texture->sprite.getGlobalBounds().height /
                                                                                               2);
    else if (res < 20)
        this->scope->entityManager.add<Entities::HealPowerUp>(LAYER::Layer1,
                                                              static_cast<GRADE>(res % 3), position.x +
                                                                                           this->texture->sprite.getGlobalBounds().width /
                                                                                           2, position.y +
                                                                                              this->texture->sprite.getGlobalBounds().height /
                                                                                              2);
    else if (res < 30)
        this->scope->entityManager.add<Entities::ShieldPowerUp>(LAYER::Layer1,
                                                                static_cast<GRADE>(res % 3), position.x +
                                                                                             this->texture->sprite.getGlobalBounds().width /
                                                                                             2, position.y +
                                                                                                this->texture->sprite.getGlobalBounds().height /
                                                                                                2);
    else if (res < 40)
        this->scope->entityManager.add<Entities::DamagePowerUp>(LAYER::Layer1,
                                                                static_cast<GRADE>(res % 3), position.x +
                                                                                             this->texture->sprite.getGlobalBounds().width /
                                                                                             2, position.y +
                                                                                                this->texture->sprite.getGlobalBounds().height /
                                                                                                2);
}


bool Entities::Ship::shoot() {
    return this->weapon->shoot(this->canons, this->position);
}

void Entities::Ship::update() {
    MOVABLE_ENTITY::update();
    if (this->health <= 0)
        this->scope->removeEntity(this);
}

void Entities::Ship::onCollision(ENTITY *other) {

}

void Entities::Ship::takeDamage(int value) {
    if (this->shield > value) {
        this->shield -= value;
    } else {
        this->health -= (value - this->shield);
        this->shield = 0;
    }
}

void Entities::Ship::gainHealth(GRADE grade) {
    switch (grade) {
        case BRONZE:
            health += 30;
            break;
        case SILVER:
            health += 60;
            break;
        case GOLD:
            health += 90;
            break;
    }
    if (health > maxHealth)
        health = maxHealth;
}

void Entities::Ship::gainShield(GRADE grade) {
    switch (grade) {
        case BRONZE:
            shield += 30;
            break;
        case SILVER:
            shield += 60;
            break;
        case GOLD:
            shield += 90;
            break;
    }
}

void Entities::Ship::gainSpeed(GRADE grade) {
    if (speed.x < 2 && speed.y < 2)
        switch (grade) {
            case BRONZE:
                speed.x *= 1.1;
                speed.y *= 1.1;
                break;
            case SILVER:
                speed.x *= 1.2;
                speed.y *= 1.2;
                break;
            case GOLD:
                speed.x *= 1.3;
                speed.y *= 1.3;
                break;
        }
}

void Entities::Ship::upgradeWeapon(GRADE grade) {
    this->weapon->upgrade(grade);
}

Entities::Ship::TEAM Entities::Ship::getTeam() {
    return this->team;
}

void Entities::Ship::moveUp() {
    if (this->position.y - this->speed.y > 0)
        MovableEntity::moveUp();
}

void Entities::Ship::moveDown() {
    if (this->position.y + this->speed.y + this->texture->sprite.getGlobalBounds().height <
        this->scope->gameService->getWindowSize().y)
        MovableEntity::moveDown();
}

void Entities::Ship::moveRight() {
    if (this->position.x + this->speed.x + this->texture->sprite.getGlobalBounds().width <
        this->scope->gameService->getWindowSize().x)
        MovableEntity::moveRight();
}

void Entities::Ship::moveLeft() {
    if (this->position.x - this->speed.x > 0)
        MovableEntity::moveLeft();
}

int Entities::Ship::getShield() {
    return this->shield;
}

