#include <SFML/Graphics.hpp>
#include <vector>
#include "../include/Aircraft.hpp"
#include "../include/Weapon.hpp"
#include "../include/Projectile.hpp"

using namespace std;

int main() {
    const float WINDOW_WIDTH = 800.0f;
    const float WINDOW_HEIGHT = 600.0f;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Sky Defender: Kryptonian Reef");
    window.setFramerateLimit(60);

    // Initialize player Aircraft and equipped Weapon
    Aircraft player(100, 300.0f, 3, 2, 375.0f, 500.0f);
    Weapon primaryWeapon("Plasma Gatling", 10, 0.2f, -1, 0);
    vector<Projectile> projectiles;

    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // 1. Handle Aircraft movement & Weapon firing
        player.handleInput(deltaTime, WINDOW_WIDTH, WINDOW_HEIGHT);
        primaryWeapon.update(deltaTime);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            float spawnX = player.getPosition().getX() + (player.getBounds().width / 2.0f) - 3.0f;
            float spawnY = player.getPosition().getY();
            primaryWeapon.fire(spawnX, spawnY, projectiles);
        }

        // 2. Update all active projectiles and remove off-screen ones
        for (size_t i = 0; i < projectiles.size(); ) {
            projectiles[i].update(deltaTime);
            if (!projectiles[i].isActive()) {
                projectiles.erase(projectiles.begin() + i);
            } else {
                ++i;
            }
        }

        // 3. Render everything
        window.clear(sf::Color(15, 45, 75)); // Deep ocean reef blue

        for (size_t i = 0; i < projectiles.size(); ++i) {
            projectiles[i].render(window);
        }
        player.render(window);

        window.display();
    }

    return 0;
}