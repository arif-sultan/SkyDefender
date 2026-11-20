#ifndef ENEMY_H
#define ENEMY_H

#include "Coordinates.h"

#include <string>
#include <iostream>

class Enemy
{
    private:

        Coordinates position;       // Composition - Enemy owns its co-ordinates
        
        int health;
        int damageOnCollision;
        
        float speed;
        float height;
        float width;

        static int enemyCounter;    // Counts the number of enemies that are alive (right now)

    public:
        // Constructors
        Enemy();
        Enemy(float x, float y, int health, float speed, int damageOnCollision, float width, float height);


        // Getters 
        int getHealth() const;
        float getSpeed() const;
        float getWidth() const;
        float getHeight() const;
        int getDamageOnCollision() const;
        const Coordinates& getPosition() const;
        bool isAlive() const;
        

        // Edges of the enemy's box 
        // (used by CollisionSystem)
        float getLeft() const;
        float getRight() const;
        float getTop() const;
        float getBottom() const;
        
        
        // delete copy methods
        // Enemies will never get copied - used through Enemy* pointers (to prevent enemy counter issues)
        Enemy(const Enemy&) = delete;
        Enemy& operator=(const Enemy&) = delete;


        // Apply Damage 
        void takeDamage(int amount);
        Enemy& operator-=(int amount);    


        // Static function - returns current enemy count (alive)
        static int getEnemyCount();

        
        // ---- Pure virtual: every derived enemy MUST define these ----
        virtual void update(float deltaTime) = 0;     // how it moves
        virtual int getScoreValue() const = 0;        // points when it dies
        
        // ---- Virtual with a default: derived classes MAY override ----
        virtual bool isOffScreen(float windowHeight) const;
        virtual bool isBoss() const;
        
        // ---- Function overloading ----
        void setPosition(float x, float y);
        void setPosition(const Coordinates& newPosition);
        
        void moveBy(float dx, float dy);
        
        // Destructor
        virtual ~Enemy();

        // input and output streams
        friend ostream& operator<<(ostream& out, const Enemy& enemy);
        friend istream& operator>>(istream& in, Enemy& enemy);
    };

#endif