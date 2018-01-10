
#include "Scope.hpp"

void SCOPE::registerCallback(sf::Keyboard::Key key, std::function<void(void)> &f) {
    this->callbacks[key].push_back(f);
}

void SCOPE::execCallbacks(sf::Keyboard::Key key) {
    for (const auto &callback : this->callbacks[key]) {
        callback();
    }
}
