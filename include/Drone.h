#ifndef DRONE_H
#define DRONE_H

#include "Enemy.h"

// Basic enemy: flies straight down the screen.
class Drone : public Enemy 
{
    private:
        int scoreValue;    // extra attribute, only for Drone and its children

    protected:
        // Lets derived classes (like ZigZagDrone) reuse Drone with their own stats
        Drone(float x, float y, int health, float speed, int damageOnCollision,
            int scoreValue);

    public:
        Drone();
        Drone(float x, float y);

        void update(float deltaTime) override;
        int getScoreValue() const override;
};

#endif
