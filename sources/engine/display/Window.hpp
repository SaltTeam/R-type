#ifndef WINDOW_HPP
# define WINDOW_HPP

# include <SFML/Window/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace Engine {
    namespace Display {
        class Window {
        private:
            sf::RenderWindow window;

        public:
            Window(unsigned int width, unsigned int height, std::string const &name) : window{
                    sf::VideoMode(width, height),
                    name} {}

            ~Window() = default;

        public:
            const sf::Window &Window::getWindow() const { return window; }

        public:
            bool isOpen() { return window.isOpen(); }

            bool pollEvent(sf::Event &event) { return window.pollEvent(event); }

            void close() { window.close(); }

            void clear() {window.clear();}

		    sf::Vector2u getSize() {return window.getSize();}
        public:
            Window() = delete;
        };
    }
}
#endif //  !WINDOW_HPP
