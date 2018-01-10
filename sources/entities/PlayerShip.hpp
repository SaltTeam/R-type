
#pragma once

#include "engine/entity/Entity.hpp"

namespace Entities{
    class PlayerShip : public ENTITY {
    public:
        PlayerShip(uint64_t id, const std::string &texturePath, bool isEnabled = true);

    protected:
        void update() override;
    };
}
