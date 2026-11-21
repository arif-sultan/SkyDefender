#include "../include/Aircraft.hpp"

Aircraft::Aircraft()
    : health(100), maxHealth(100), speed(300.0f), lives(3), bombs(2),
      shieldActive(false), position(375.0f, 500.0f) {
    body.setSize(sf::Vector2f(50.0f, 50.0f));
    body.setFillColor(sf::Color::Green);
    body.setPosition({position.getX(), position.getY()});
}

Aircraft::Aircraft(int initHealth, float initSpeed, int initLives, int initBombs, float startX, float startY)
    : health(initHealth), maxHealth(initHealth), speed(initSpeed),
      lives(initLives), bombs(initBombs), shieldActive(false), position(startX, startY) {
    body.setSize(sf::Vector2f(50.0f, 50.0f));
    body.setFillColor(sf::Color::Green);
    body.setPosition({position.getX(), position.getY()});
}

Aircraft::~Aircraft() {}

void Aircraft::move(float dirX, float dirY, float deltaTime, float windowWidth, float windowHeight) {
    float newX = position.getX() + dirX * speed * deltaTime;
    float newY = position.getY() + dirY * speed * deltaTime;

    // Keep aircraft inside playable screen area
    if (newX < 0.0f) newX = 0.0f;
    if (newY < 0.0f) newY = 0.0f;
    if (newX + body.getSize().x > windowWidth) newX = windowWidth - body.getSize().x;
    if (newY + body.getSize().y > windowHeight) newY = windowHeight - body.getSize().y;

    position.setPosition(newX, newY);
    body.setPosition({position.getX(), position.getY()});
}

void Aircraft::handleInput(float deltaTime, float windowWidth, float windowHeight) {
    float dirX = 0.0f;
    float dirY = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        dirX = -1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        dirX = 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        dirY = -1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        dirY = 1.0f;
    }

    move(dirX, dirY, deltaTime, windowWidth, windowHeight);
}

void Aircraft::takeDamage(int amount) {
    // Reuses the overloaded version (OOP Requirement B.10: Reuse)
    takeDamage(amount, false);
}

void Aircraft::takeDamage(int amount, bool bypassShield) {
    if (shieldActive && !bypassShield) {
        return;
    }
    if (amount <= 0) {
        return;
    }

    health -= amount;
    if (health <= 0) {
        lives--;
        if (lives > 0) {
            respawn(375.0f, 500.0f);
        } else {
            health = 0;
        }
    }
}

void Aircraft::heal(int amount) {
    if (amount > 0) {
        health += amount;
        if (health > maxHealth) {
            health = maxHealth;
        }
    }
}

bool Aircraft::useBomb() {
    if (bombs > 0) {
        bombs--;
        return true;
    }
    return false;
}

void Aircraft::respawn(float startX, float startY) {
    health = maxHealth;
    setShield(false); // Resets both shieldActive and the 3.0f cyan outline
    position.setPosition(startX, startY);
    body.setPosition({startX, startY});
}

void Aircraft::setShield(bool active) {
    shieldActive = active;
    if (active == true) {
        body.setOutlineThickness(3.0f);
    } else {
        body.setOutlineThickness(0.0f);
    }
    body.setOutlineColor(sf::Color::Cyan);
}

void Aircraft::render(sf::RenderWindow& window) const {
    window.draw(body);
}

int Aircraft::getHealth() const { return health; }
int Aircraft::getMaxHealth() const { return maxHealth; }
float Aircraft::getSpeed() const { return speed; }
int Aircraft::getLives() const { return lives; }
int Aircraft::getBombs() const { return bombs; }
bool Aircraft::isShieldActive() const { return shieldActive; }
bool Aircraft::isAlive() const { return lives > 0; }
const Coordinates& Aircraft::getPosition() const { return position; }
sf::FloatRect Aircraft::getBounds() const { return body.getGlobalBounds(); }

void Aircraft::setSpeed(float newSpeed) {
    if (newSpeed > 0.0f) {
        speed = newSpeed;
    }
}