#include "../include/Projectile.hpp"

Projectile::Projectile()
    : damage(10), speed(600.0f), active(true), position(0.0f, 0.0f) {
    shape.setSize(sf::Vector2f(6.0f, 16.0f));
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(position.getX(), position.getY());
}

Projectile::Projectile(int initDamage, float initSpeed, float startX, float startY)
    : damage(initDamage), speed(initSpeed), active(true), position(startX, startY) {
    shape.setSize(sf::Vector2f(6.0f, 16.0f));
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(position.getX(), position.getY());
}

Projectile::~Projectile() {}

void Projectile::update(float deltaTime) {
    if (!active) {
        return;
    }

    // Move upward (negative Y direction in SFML)
    float newY = position.getY() - speed * deltaTime;
    position.setY(newY);
    shape.setPosition(position.getX(), position.getY());

    // Deactivate once it leaves the top of the screen
    if (newY + shape.getSize().y < 0.0f) {
        active = false;
    }
}

void Projectile::render(sf::RenderWindow& window) const {
    if (active) {
        window.draw(shape);
    }
}

void Projectile::deactivate() {
    active = false;
}

int Projectile::getDamage() const {
    return damage;
}

float Projectile::getSpeed() const {
    return speed;
}

bool Projectile::isActive() const {
    return active;
}

const Coordinates& Projectile::getPosition() const {
    return position;
}

sf::FloatRect Projectile::getBounds() const {
    return shape.getGlobalBounds();
}