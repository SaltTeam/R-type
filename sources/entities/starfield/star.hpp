//
// Created by delacr_a on 21/01/18.
//

#pragma once

#include "engine/ForwardDeclaration.hpp"
#include "engine/entity/Entity.hpp"
#include "engine/entity/MovableEntity.hpp"

namespace Entities {
    class Star : public MOVABLE_ENTITY {
    public:
        Star(SCOPE *scope, uint64_t id, network::protocol::PlayerColor playerColor);

    protected:
        void update() override;

    };
}
