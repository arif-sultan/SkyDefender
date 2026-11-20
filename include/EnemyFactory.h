#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include "Enemy.h"

// DESIGN PATTERN: Factory
// The rest of the game asks the factory for an enemy and gets back an
// Enemy* without needing to know how each one is built.
class EnemyFactory {
private:
    float arenaWidth;   // the Boss needs to know how wide the play area is

public:
    EnemyFactory();
    explicit EnemyFactory(float arenaWidth);

    // Function overloading: give x and y, or a Coordinates object.
    // The CALLER owns the returned pointer (and must delete it).
    Enemy* createDrone(float x, float y) const;
    Enemy* createDrone(const Coordinates& position) const;

    Enemy* createZigZagDrone(float x, float y) const;
    Enemy* createZigZagDrone(const Coordinates& position) const;

    Enemy* createBoss(float x, float y) const;
};

#endif
