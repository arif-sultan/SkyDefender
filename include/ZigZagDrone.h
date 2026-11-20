#ifndef ZIGZAGDRONE_H
#define ZIGZAGDRONE_H

#include "Drone.h"

// Enemy -> Drone -> ZigZagDrone
// Moves down like a Drone, but also sways left and right.
class ZigZagDrone : public Drone 
{
    private:
        float startX;
        float amplitude;     // how far it sways from startX
        float swaySpeed;     // how fast it sways
        float elapsedTime;

    public:
        ZigZagDrone();
        ZigZagDrone(float x, float y, float amplitude = 80.0f);

        void update(float deltaTime) override;
};

#endif