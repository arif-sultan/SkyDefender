#include "../include/ZigZagDrone.h"
#include <cmath>

ZigZagDrone::ZigZagDrone() : Drone(0.0f, 0.0f, 20, 140.0f, 10, 150), startX(0.0f), amplitude(80.0f), swaySpeed(3.0f), elapsedTime(0.0f) 
{

}

ZigZagDrone::ZigZagDrone(float x, float y, float amplitude) : Drone(x, y, 20, 140.0f, 10, 150), startX(x), amplitude(amplitude), swaySpeed(3.0f), elapsedTime(0.0f) 
{

}

void ZigZagDrone::update(float deltaTime) 
{
    Drone::update(deltaTime);   // REUSE: the "move down" logic lives in Drone
    elapsedTime += deltaTime;
    float newX = startX + amplitude * std::sin(elapsedTime * swaySpeed);
    setPosition(newX, getPosition().getY());
}
