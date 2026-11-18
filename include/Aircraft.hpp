#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "Coordinates.hpp"
using namespace std;

class Aircraft {
private:
    int health;
    int maxHealth;
    float speed;
    int lives;
    int bombs;
    bool shieldActive;
    Coordinates position;    // Composition: Aircraft owns Coordinates
    sf::RectangleShape body; // SFML visual representation

public:
    // Default and Parameterized Constructors using Member Initializer Lists
    Aircraft();
    Aircraft(int initHealth, float initSpeed, int initLives, int initBombs, float startX, float startY);

    // Destructor
    ~Aircraft();

    // Movement & Boundary Enforcement
    void move(float dirX, float dirY, float deltaTime, float windowWidth, float windowHeight);
    void handleInput(float deltaTime, float windowWidth, float windowHeight);

    // Function Overloading (OOP Requirement B.4)
    void takeDamage(int amount);
    void takeDamage(int amount, bool bypassShield);

    // Gameplay Mechanics
    void heal(int amount);
    bool useBomb();
    void respawn(float startX, float startY);
    void setShield(bool active);

    // Rendering
    void render(sf::RenderWindow& window) const;

    // Const-correct Getters
    int getHealth() const;
    int getMaxHealth() const;
    float getSpeed() const;
    int getLives() const;
    int getBombs() const;
    bool isShieldActive() const;
    bool isAlive() const;
    const Coordinates& getPosition() const;
    sf::FloatRect getBounds() const;

    // Setters
    void setSpeed(float newSpeed);
};

#endif