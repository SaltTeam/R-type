
#pragma once

namespace Entities {
    class BaseEntity {
    public:
        bool isEnabled;

        explicit BaseEntity(bool isEnabled = false) : isEnabled(isEnabled) {}

        virtual ~BaseEntity() = default;

        virtual void update() = 0;
    };
}
