//
// Created by delacr_a on 11/01/18.
//

#pragma once

#include "engine/ForwardDeclaration.hpp"

namespace Engine {
    namespace Entities {

        class MovableEntity : public ENTITY {
            friend NET_SERVICE;

        protected:
            sf::Vector2f speed;

        public:

            MovableEntity(SCOPE *scope, uint64_t id, network::protocol::PlayerColor playerColor,
                          network::protocol::Update updateType = network::protocol::Update::Instanciated,
                          uint16_t refreshTime = 1, bool isEnabled = true,
                          float const &x = 0, float const &y = 0, float const &x_speed = 0, float const &y_speed = 0)
                    : BaseEntity(scope, id, playerColor, updateType, refreshTime, isEnabled, x, y),
                      speed({x_speed, y_speed}) {};

            void update() override;

            virtual void moveUp();

            virtual void moveDown();

            virtual void moveRight();

            virtual void moveLeft();

            virtual void move();

            void setSpeed(sf::Vector2f const &speed);

            void setSpeed(float const &x_speed, float const &y_speed);

            void setSpeed(float const &xy_speed);
        };
    }
}
