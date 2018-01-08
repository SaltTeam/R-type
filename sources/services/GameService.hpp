
#pragma once

#include "scopes/BaseScope.hpp"
#include "services/BaseService.hpp"

#define SCOPE Scopes::BaseScope

namespace Services {
    class GameService : public Services::BaseService {
        friend Engine;
        friend Manager<Services::BaseService>;

    private:
        bool removeScope = false;
        bool addScope = false;
        SCOPE *scopeToAdd = nullptr;

        Manager<SCOPE> scopes;

    public:
        template<typename T>
        void registerBaseScope() {
            if (this->scopes.elements.size() == 0)
                this->scopes.add<T>(this);
        }

        template<typename T>
        void pushScope() {
            this->scopeToAdd = new T(this);
            this->addScope = true;
        }

        void popScope() {
            this->removeScope = true;
        }

    private:
        explicit GameService(Engine *e);

        ~GameService() override;

        void initialize() override;

        void shutdown() override;

        void earlyUpdate() override;

        void update() override;

        void lateUpdate() override;
    };
};

#undef SCOPE
