#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "Enemy.h"
#include "EnemyFactory.h"

// Owns and manages every enemy in the level.
//  - COMPOSITION with Enemy: the manager creates enemies with new and
//    deletes them. When the manager dies, all its enemies die too.
//  - POLYMORPHISM: the array holds Enemy* but each update() call runs
//    the DERIVED class version.
class EnemyManager {
private:
    int capacity;           // maximum number of enemies at once
    int count;              // how many enemies are in the array right now
    Enemy** enemies;        // dynamic array of Enemy pointers (size = capacity)

    EnemyFactory factory;
    float arenaWidth;
    float arenaHeight;
    float spawnInterval;    // seconds between automatic spawns
    float spawnTimer;
    int stage;

    float randomX() const;      // helper: random spot across the top
    void removeAt(int index);   // helper: deletes one enemy and closes the gap

public:
    EnemyManager();
    EnemyManager(float arenaWidth, float arenaHeight);

    // Owns memory (new), so: destructor + copying disabled
    ~EnemyManager();
    EnemyManager(const EnemyManager&) = delete;
    EnemyManager& operator=(const EnemyManager&) = delete;

    // Function overloading: exact position, or random spot above the screen
    // These return nullptr if the array is full.
    Enemy* spawnDrone(float x, float y);
    Enemy* spawnDrone();
    Enemy* spawnZigZagDrone(float x, float y);
    Enemy* spawnZigZagDrone();
    Enemy* spawnBoss();                               // enters at top centre

    void update(float deltaTime);                     // move + auto-spawn
    int removeDefeated();                             // deletes dead/off-screen; returns points earned
    void clear();                                     // delete everything (restart / game over)

    void setStage(int newStage);                      // higher stage = faster spawns

    // CollisionSystem loops i = 0 .. getActiveCount()-1 and uses getEnemy(i)
    Enemy* getEnemy(int index) const;
    int getActiveCount() const;
    bool isBossAlive() const;
};

#endif