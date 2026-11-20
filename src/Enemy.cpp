#include "../include/Enemy.h"

int Enemy::enemyCounter = 0;


// ---------- Constructors ---------->
Enemy::Enemy() : health(1), speed(0.0f), width(0.0f), height(0.0f), damageOnCollision(0), position()        // why not change health to 100
{
    ++enemyCounter;         
}

Enemy::Enemy(float x, float y, int health, float speed, int damageOnCollision, float width, float height) : health(health), speed(speed), width(width), height(height), damageOnCollision(damageOnCollision), position(x, y) 
{
    ++enemyCounter;
}
// <---------- Constructors ----------


// ---------- Getters ---------->
int Enemy::getHealth() const 
{ 
    return health; 
}

float Enemy::getSpeed() const 
{ 
    return speed; 
}

float Enemy::getWidth() const 
{ 
    return width; 
}

float Enemy::getHeight() const 
{ 
    return height; 
}

int Enemy::getDamageOnCollision() const 
{ 
    return damageOnCollision; 
}

const Coordinates& Enemy::getPosition() const 
{ 
    return position; 
}

bool Enemy::isAlive() const 
{ 
    return health > 0; 
}
// <---------- Getters ----------


// ---------- Damage ---------->
void Enemy::takeDamage(int amount) 
{
    if (amount <= 0) 
    {
        return;
    }
    
    health -= amount;
    
    if (health < 0)
    {
        health = 0;
    } 
}

Enemy& Enemy::operator-=(int amount) 
{
    takeDamage(amount);
    return (*this);
}
// <---------- Damage ----------


// ---------- Enemy Counter ---------->
int Enemy::getEnemyCount() 
{
    return enemyCounter;
}
// <---------- Enemy Counter ----------


// ---------- Enemy Output ---------->
ostream& operator<<(std::ostream& out, const Enemy& enemy) 
{
    out << "Enemy [hp " << enemy.getHealth()
    << ", pos (" << enemy.getPosition().getX() << ", "
    << enemy.getPosition().getY() << ")]";

    return out;
}
// <---------- Enemy Output ----------


// ---------- Enemy Input ---------->
istream& operator>>(std::istream& in, Enemy& enemy) 
{
    float x = 0.0f;
    float y = 0.0f;
    
    std::cout << "Enter health: ";
    in >> enemy.health;
    std::cout << "Enter speed: ";
    in >> enemy.speed;
    std::cout << "Enter width: ";
    in >> enemy.width;
    std::cout << "Enter height: ";
    in >> enemy.height;
    std::cout << "Enter damage on collision: ";
    in >> enemy.damageOnCollision;
    std::cout << "Enter x position: ";
    in >> x;
    std::cout << "Enter y position: ";
    in >> y;
    
    if (in) 
    {                                   // only apply the position if reading worked
        enemy.position.setPosition(x, y);
    }
    
    return in;
}
// <---------- Enemy Input ----------


// ---------- Movement (overloaded) ---------->

void Enemy::setPosition(float x, float y) 
{
    position.setPosition(x, y);
}

void Enemy::setPosition(const Coordinates& newPosition) 
{
    position = newPosition;
}

void Enemy::moveBy(float dx, float dy) 
{
    position = position + Coordinates(dx, dy);   // reuses Coordinates::operator+
}
// <---------- Movement (overloaded) ----------


// ----------- position ------------->
// position is the CENTRE of the enemy
float Enemy::getLeft() const   
{ 
    return position.getX() - width / 2.0f;
}

float Enemy::getRight() const  
{ 
    return position.getX() + width / 2.0f; 
}

float Enemy::getTop() const    
{ 
    return position.getY() - height / 2.0f; 
}

float Enemy::getBottom() const 
{ 
    return position.getY() + height / 2.0f; 
}
// <----------- position -------------


// ---------- Virtual defaults ---------->
bool Enemy::isOffScreen(float windowHeight) const 
{
    // Off screen once the TOP edge has passed the bottom of the window.
    return getTop() > windowHeight;
}

bool Enemy::isBoss() const 
{
    return false;
}
// <---------- Virtual defaults ----------


// ---------- Destructor ---------->
Enemy::~Enemy() {
    --enemyCounter;
}
// <---------- Destructor ----------