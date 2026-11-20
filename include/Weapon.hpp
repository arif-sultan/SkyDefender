#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>
#include <vector>
#include "Projectile.hpp"
using namespace std;

class Weapon {
private:
    string name;
    int damage;
    float fireRate;       // Cooldown in seconds between shots
    int ammo;             // -1 represents infinite ammo
    int cost;
    float cooldownTimer;  // Tracks time since last shot

public:
    // Constructors & Destructor
    Weapon();
    Weapon(const string& weaponName, int initDamage, float initFireRate, int initAmmo, int initCost);
    ~Weapon();

    // Update cooldown & Fire projectiles
    void update(float deltaTime);
    bool canFire() const;
    void fire(float startX, float startY, vector<Projectile>& projectiles);

    // Ammo management
    void reload(int amount);

    // Const-correct Getters
    string getName() const;
    int getDamage() const;
    float getFireRate() const;
    int getAmmo() const;
    int getCost() const;
};

#endif