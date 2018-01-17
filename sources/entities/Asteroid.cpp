
#include <iostream>
#include <engine/scope/Scope.hpp>
#include "Asteroid.hpp"

static std::map<int, std::string> paths = {{0, "resources/sprites/Meteors/meteorGrey_big1.png"},
					   {1, "resources/sprites/Meteors/meteorGrey_big2.png"},
					   {2, "resources/sprites/Meteors/meteorGrey_big3.png"},
					   {3, "resources/sprites/Meteors/meteorGrey_big4.png"},
					   {4, "resources/sprites/Meteors/meteorGrey_med1.png"},
					   {5, "resources/sprites/Meteors/meteorGrey_med2.png"},
					   {6, "resources/sprites/Meteors/meteorGrey_small1.png"},
					   {7, "resources/sprites/Meteors/meteorGrey_small2.png"},
					   {8, "resources/sprites/Meteors/meteorGrey_tiny1.png"},
					   {9, "resources/sprites/Meteors/meteorGrey_tiny2.png"}};

Entities::Asteroid::Asteroid(SCOPE *scope, uint64_t id, const std::string &texturePath, bool isEnabled,
			     const float &x, const float &y)
    : MovableEntity(scope, id, isEnabled, x, y) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist_speed(-0.2, 0.2);

    this->setTexture(texturePath);
    this->setSpeed(dist_speed(mt), dist_speed(mt));
    std::function<void(ENTITY *)> f = std::bind(&Asteroid::onCollision, this, std::placeholders::_1);
    this->registerCollisionBox(this->texture->sprite.getGlobalBounds(), f);
}

Entities::Asteroid::Asteroid(SCOPE *scope, uint64_t id, bool isEnabled,
			     const float &x, const float &y)
    : MovableEntity(scope, id, isEnabled, x, y) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist_speed(-0.2, 0.2);
    std::uniform_real_distribution<float> dist_path(0, 9);

    this->setTexture(paths[dist_path(mt)]);
    this->setSpeed(dist_speed(mt), dist_speed(mt));

    std::function<void(ENTITY *)> f = std::bind(&Asteroid::onCollision, this, std::placeholders::_1);
    this->registerCollisionBox(this->texture->sprite.getGlobalBounds(), f);
}

void Entities::Asteroid::update() {
    this->move();
    MOVABLE_ENTITY::update();
}

void Entities::Asteroid::onCollision(ENTITY *other) {
    this->scope->removeEntity(this);
}
