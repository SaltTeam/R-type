
#include "Scope.hpp"

void SCOPE::registerCallback(sf::Keyboard::Key key, std::function<void(void)> &f) {
  this->callbacks[key].push_back(f);
}

void SCOPE::execCallbacks() {
  for (const auto &registered : this->callbacks) {
    if (sf::Keyboard::isKeyPressed(registered.first))
      for (auto &callback : registered.second)
	callback();
  }
}
