#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Aircraft.hpp"
#include "EnemyManager.h"
#include "Weapon.hpp"
#include "AudioManager.hpp"

// Every screen is represented by one game state.
enum class GameState
{
    MainMenu,
    Playing,
    Hangar,
    Paused,
    GameOver,
    Victory,
    Controls
};

class Game
{
private:
    sf::RenderWindow window;
    sf::Font font;
    bool fontLoaded;
    AudioManager audio;

    GameState state;
    Aircraft player;
    EnemyManager enemyManager;

    std::vector<Projectile> projectiles;
    std::vector<Weapon> weapons;
    std::vector<bool> weaponOwned;

    int selectedWeapon;
    int equippedWeapon;
    int score;
    int credits;
    int stage;

    sf::Clock gameClock;
    float damageTimer;

    void handleEvents();
    void handleMenuInput(sf::Keyboard::Key key);
    void update(float deltaTime);
    void render();

    void drawText(const std::string &value, float x, float y, unsigned int size, sf::Color color = sf::Color::White);
    void drawButton(const std::string &label, float x, float y, float width, float height, bool selected);
    void drawMainMenu();
    void drawHangar();
    void drawGameplay();
    void drawPauseMenu();
    void drawEndScreen(bool victory);
    void drawControls();

    void startNewGame();
    void updateGameplay(float deltaTime);
    void checkCollisions();
    void drawEnemies();

public:
    Game();
    void run();
};

#endif
