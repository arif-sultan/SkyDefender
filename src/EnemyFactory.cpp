#include "../include/EnemyFactory.h"
#include "../include/Drone.h"
#include "../include/ZigZagDrone.h"
#include "../include/Boss.h"

EnemyFactory::EnemyFactory() : arenaWidth(800.0f) 
{

}

EnemyFactory::EnemyFactory(float arenaWidth) : arenaWidth(arenaWidth) 
{

}

Enemy* EnemyFactory::createDrone(float x, float y) const 
{
    return new Drone(x, y);
}

Enemy* EnemyFactory::createDrone(const Coordinates& position) const 
{
    return createDrone(position.getX(), position.getY());
}

Enemy* EnemyFactory::createZigZagDrone(float x, float y) const 
{
    return new ZigZagDrone(x, y);
}

Enemy* EnemyFactory::createZigZagDrone(const Coordinates& position) const 
{
    return createZigZagDrone(position.getX(), position.getY());
}

Enemy* EnemyFactory::createBoss(float x, float y) const 
{
    return new Boss(x, y, arenaWidth);
}
