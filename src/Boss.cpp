#include "../include/Boss.h"

Boss::Boss() : Enemy(400.0f, -100.0f, 500, 100.0f, 50, 150.0f, 100.0f), scoreValue(2000), arenaWidth(800.0f), targetY(100.0f), direction(1) 
{

}

Boss::Boss(float x, float y, float arenaWidth) : Enemy(x, y, 500, 100.0f, 50, 150.0f, 100.0f), scoreValue(2000), arenaWidth(arenaWidth), targetY(100.0f), direction(1) 
{

}

void Boss::update(float deltaTime) 
{
    // Phase 1: descend into the arena
    if (getPosition().getY() < targetY) 
    {
        moveBy(0.0f, getSpeed() * deltaTime);
        return;
    }

    // Phase 2: patrol, bouncing off the side walls
    moveBy(direction * getSpeed() * deltaTime, 0.0f);

    if (getLeft() < 0.0f) 
    {
        setPosition(getWidth() / 2.0f, getPosition().getY());
        direction = 1;
    } 
    else if (getRight() > arenaWidth) 
    {
        setPosition(arenaWidth - getWidth() / 2.0f, getPosition().getY());
        direction = -1;
    }
}

int Boss::getScoreValue() const 
{
    return scoreValue;
}

bool Boss::isOffScreen(float) const 
{
    return false;
}

bool Boss::isBoss() const 
{
    return true;
}
