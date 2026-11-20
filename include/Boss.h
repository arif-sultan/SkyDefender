#ifndef BOSS_H
#define BOSS_H

#include "Enemy.h"

class Boss: public Enemy
{
    private:
        int scoreValue;
        float arenaWidth;
        float targetY;      // where the boss stops descending
        int direction;      // +1 = moving right, -1 = moving left

    public:
        Boss();
        Boss(float x, float y, float arenaWidth);

        void update(float deltaTime) override;
        int getScoreValue() const override;
        bool isOffScreen(float windowHeight) const override;   // a boss never leaves
        bool isBoss() const override;
};

#endif