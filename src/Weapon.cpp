#include "../include/Weapon.hpp"

Weapon::Weapon()
    : name("Standard Blaster"), damage(10), fireRate(0.25f),
      ammo(-1), cost(0), cooldownTimer(0.0f) {}

Weapon::Weapon(const string& weaponName, int initDamage, float initFireRate, int initAmmo, int initCost)
    : name(weaponName), damage(initDamage), fireRate(initFireRate),
      ammo(initAmmo), cost(initCost), cooldownTimer(0.0f) {}

Weapon::~Weapon() {}

void Weapon::update(float deltaTime) {
    if (cooldownTimer > 0.0f) {
        cooldownTimer -= deltaTime;
        if (cooldownTimer < 0.0f) {
            cooldownTimer = 0.0f;
        }
    }
}

bool Weapon::canFire() const {
    bool hasAmmo = (ammo == -1 || ammo > 0);
    return (cooldownTimer <= 0.0f) && hasAmmo;
}

void Weapon::fire(float startX, float startY, vector<Projectile>& projectiles) {
    if (!canFire()) {
        return;
    }

    // Spawn a new projectile at the aircraft's firing coordinates
    projectiles.push_back(Projectile(damage, 600.0f, startX, startY));

    // Reset cooldown timer and decrement ammo if finite
    cooldownTimer = fireRate;
    if (ammo > 0) {
        ammo--;
    }
}

void Weapon::reload(int amount) {
    if (ammo != -1 && amount > 0) {
        ammo += amount;
    }
}

string Weapon::getName() const {
    return name;
}

int Weapon::getDamage() const {
    return damage;
}

float Weapon::getFireRate() const {
    return fireRate;
}

int Weapon::getAmmo() const {
    return ammo;
}

int Weapon::getCost() const {
    return cost;
}