#include <SFML/Graphics.hpp>

int main() {
    // Create a windowed mode screen for Sky Defender test
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sky Defender: Kryptonian Reef - Test");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Blue); // Placeholder for ocean/reef background
        // TODO: Draw game entities here
        window.display();
    }

    return 0;
}