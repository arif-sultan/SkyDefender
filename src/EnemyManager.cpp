#include "../include/EnemyManager.h"
#include <cstdlib>      // rand()

const float SPAWN_Y = -40.0f;       // just above the visible screen
const float SPAWN_MARGIN = 40.0f;
const int MAX_ENEMIES = 50;

EnemyManager::EnemyManager() 
    : capacity(MAX_ENEMIES), count(0), enemies(new Enemy*[MAX_ENEMIES]),
      factory(800.0f), arenaWidth(800.0f), arenaHeight(600.0f),
      spawnInterval(2.0f), spawnTimer(0.0f), stage(1) 
{

}

EnemyManager::EnemyManager(float arenaWidth, float arenaHeight)
    : capacity(MAX_ENEMIES), count(0), enemies(new Enemy*[MAX_ENEMIES]),
      factory(arenaWidth), arenaWidth(arenaWidth), arenaHeight(arenaHeight),
      spawnInterval(2.0f), spawnTimer(0.0f), stage(1) 
{

}

EnemyManager::~EnemyManager() {
    clear();             // delete every enemy
    delete[] enemies;    // then delete the array itself
}

float EnemyManager::randomX() const 
{
    int range = (int)(arenaWidth - 2 * SPAWN_MARGIN);
    return SPAWN_MARGIN + (float)(rand() % (range + 1));
}

Enemy* EnemyManager::spawnDrone(float x, float y) 
{
    if (count == capacity) {
        return nullptr;                       // array is full
    }
    Enemy* enemy = factory.createDrone(x, y);
    enemies[count] = enemy;
    count++;
    return enemy;
}

Enemy* EnemyManager::spawnDrone() 
{
    return spawnDrone(randomX(), SPAWN_Y);
}

Enemy* EnemyManager::spawnZigZagDrone(float x, float y) 
{
    if (count == capacity) {
        return nullptr;
    }
    Enemy* enemy = factory.createZigZagDrone(x, y);
    enemies[count] = enemy;
    count++;
    return enemy;
}

Enemy* EnemyManager::spawnZigZagDrone() 
{
    return spawnZigZagDrone(randomX(), SPAWN_Y);
}

Enemy* EnemyManager::spawnBoss() 
{
    if (count == capacity) {
        return nullptr;
    }
    Enemy* enemy = factory.createBoss(arenaWidth / 2.0f, -100.0f);
    enemies[count] = enemy;
    count++;
    return enemy;
}

void EnemyManager::update(float deltaTime) 
{
    // 1. Automatic spawning (paused while a boss fight is on)
    if (!isBossAlive()) {
        spawnTimer += deltaTime;
        if (spawnTimer >= spawnInterval) {
            spawnTimer = 0.0f;
            bool useZigZag = (stage >= 2) && (rand() % 2 == 1);
            if (useZigZag) {
                spawnZigZagDrone();
            } else {
                spawnDrone();
            }
        }
    }

    // 2. Update every enemy. Each call runs the DERIVED version (polymorphism).
    for (int i = 0; i < count; i++) {
        enemies[i]->update(deltaTime);
    }
}

// Deletes enemy number "index" and moves the LAST enemy into its place
// so the array has no gaps.
void EnemyManager::removeAt(int index) 
{
    delete enemies[index];
    enemies[index] = enemies[count - 1];
    count--;
}

int EnemyManager::removeDefeated() 
{
    int pointsEarned = 0;
    int i = 0;
    while (i < count) {
        if (!enemies[i]->isAlive()) {
            pointsEarned += enemies[i]->getScoreValue();   // killed by the player: award points
            removeAt(i);                                   // don't do i++ : a new enemy is now at i
        } else if (enemies[i]->isOffScreen(arenaHeight)) {
            removeAt(i);                                   // escaped: no points
        } else {
            i++;
        }
    }
    return pointsEarned;
}

void EnemyManager::clear() 
{
    for (int i = 0; i < count; i++) {
        delete enemies[i];
    }
    count = 0;
}

void EnemyManager::setStage(int newStage) 
{
    if (newStage < 1) {
        stage = 1;
    } else {
        stage = newStage;
    }

    spawnInterval = 2.0f - 0.25f * (stage - 1);
    if (spawnInterval < 0.5f) {
        spawnInterval = 0.5f;                 // never faster than 0.5 seconds
    }
}

Enemy* EnemyManager::getEnemy(int index) const 
{
    if (index < 0 || index >= count) {
        return nullptr;
    }
    return enemies[index];
}

int EnemyManager::getActiveCount() const 
{
    return count;
}

bool EnemyManager::isBossAlive() const 
{
    for (int i = 0; i < count; i++) {
        if (enemies[i]->isBoss() && enemies[i]->isAlive()) {
            return true;
        }
    }
    return false;
}