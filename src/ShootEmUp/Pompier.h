#pragma once
#include "Entity.h"

class Pompier : public Entity
{
private:
    float cooldown = 0;
    float shotspeed = 1.00;
    float projectilespeed = 180;

    int targetY = rand() % GetScene()->GetWindowHeight(); // Cible al�atoire pour Y
    float targetX = 0; // Cible pour X
    float movementSpeed = 100; // Vitesse de base
    int hp = 5;

    float randomX = (rand() % 30) / 100.0f + 0.6f;

public:
    Player* pPlayer = GetScene<GameScene>()->GetPlayer();
    void OnCollision(Entity* other) override;
    void OnUpdate() override;
};
