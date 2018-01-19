//
// Created by vivaldi91 on 18/01/18.
//

#pragma once

#include <entities/ships/Ship.hpp>
#include <entities/weapons/sub/Laser3.hpp>

namespace Entities {
    class Enemy4 : public Ship {
        enum State{
            State1 = 0,
            State2,
            State3,
            State4,
            State5,
            State6
        };

    private:
        std::uniform_int_distribution<std::mt19937::result_type> dist10;
        std::mt19937 rng;
        float OriginalXPosition;
        float OriginalYPosition;
        State state;

    public:
        Enemy4(SCOPE *scope, uint64_t id = 0, bool isEnabled = true, const float &x = 0, const float &y = 0)
                : Ship(scope, id, "resources/sprites/ships/enemy/ship4/base.png", isEnabled, Entities::Ship::GAME, x,
                       y, 0.25, 0.1, 50) {
            this->weapon = new Entities::Laser3(scope, this->team);
            this->weapon->setYSpeed(-(this->weapon->getYSpeed()));
            this->OriginalXPosition = this->position.x;
            this->OriginalYPosition = this->position.y;
            this->canons.push_back({this->texture->sprite.getGlobalBounds().width / 2 - 8, this->texture->sprite.getGlobalBounds().height / 2 + 5});
            this->canons.push_back({this->texture->sprite.getGlobalBounds().width / 2 + 8, this->texture->sprite.getGlobalBounds().height / 2 + 5});
            this->state = State6;
            this->speed.x = 0;
            this->rng.seed(std::random_device()());
            std::uniform_int_distribution<std::mt19937::result_type> dist6(1,10000);
            dist10 = dist6;
        }

        void update() override {
            int random_variable = std::rand();
            this->move();
            if (dist10(rng) % 1005 == 0)
                this->shoot();
            Ship::update();
            switch (this->state)
            {
                case(State1):
                    state1();
                    break;
                case(State2):
                    state2();
                    break;
                case(State3):
                    state3();
                    break;
                case(State4):
                    state4();
                    break;
                case(State5):
                    state5();
                    break;
                case(State6):
                    state6();
                    break;
                default:
                    break;
            }
        }

        void state1() {
            if (this->position.y < this->OriginalYPosition - 200)
            {
                this->OriginalYPosition = this->position.y;
                this->speed.x = -(this->speed.y);
                this->speed.y = 0;
                this->state = State2;
            }
        }

        void state2(){
            if (this->position.x > this->OriginalXPosition + 200)
            {
                this->OriginalXPosition = this->position.x;
                this->speed.y = this->speed.x;
                this->speed.x = 0;
                this->state = State3;
            }
        }

        void state3(){
            if (this->position.y > this->OriginalYPosition + 200)
            {
                this->OriginalYPosition = this->position.y;
                this->speed.y = -(this->speed.y);
                this->state = State4;
            }
        }

        void state4(){
            if (this->position.y < this->OriginalYPosition - 200)
            {
                this->OriginalYPosition = this->position.y;
                this->speed.x = this->speed.y;
                this->speed.y = 0;
                this->state = State5;
            }
        }

        void state5(){
            if (this->position.x < this->OriginalXPosition - 200)
            {
                this->OriginalXPosition = this->position.x;
                this->speed.y = -(this->speed.x);
                this->speed.x = 0;
                this->state = State6;
            }
        }

        void state6(){
            if (this->position.y > this->OriginalYPosition + 200)
            {
                this->OriginalYPosition = this->position.y;
                this->speed.y = -(this->speed.y);
                this->state = State1;
            }
        }
    };
}
