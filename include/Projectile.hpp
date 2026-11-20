#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>
#include "Coordinates.hpp"
using namespace std;

class Projectile {
private:
    int damage;
    float speed;
    bool active;
    Coordinates position;    // Composition: Projectile has Coordinates
    sf::RectangleShape shape;

public:
    // Constructors & Destructor
    Projectile();
    Projectile(int initDamage, float initSpeed, float startX, float startY);
    ~Projectile();

    // Movement & State Update
    void update(float deltaTime);
    void render(sf::RenderWindow& window) const;
    void deactivate();

    // Const-correct Getters
    int getDamage() const;
    float getSpeed() const;
    bool isActive() const;
    const Coordinates& getPosition() const;
    sf::FloatRect getBounds() const;
};

#endif