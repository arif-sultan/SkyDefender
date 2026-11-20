#include "../include/Drone.h"

#define DRONE_SIZE 40.0f

Drone::Drone() : Enemy(0.0f, 0.0f, 30, 120.0f, 10, DRONE_SIZE, DRONE_SIZE), scoreValue(100) 
{

}

Drone::Drone(float x, float y) : Enemy(x, y, 30, 120.0f, 10, DRONE_SIZE, DRONE_SIZE), scoreValue(100) 
{

}

Drone::Drone(float x, float y, int health, float speed, int damageOnCollision, int scoreValue) : Enemy(x, y, health, speed, damageOnCollision, DRONE_SIZE, DRONE_SIZE), scoreValue(scoreValue) 
{

}

void Drone::update(float deltaTime) 
{
    moveBy(0.0f, getSpeed() * deltaTime);   // straight down
}

int Drone::getScoreValue() const {
    return scoreValue;
}
