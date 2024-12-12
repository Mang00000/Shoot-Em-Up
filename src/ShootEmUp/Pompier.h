#pragma once
#include "Entity.h"

class Pompier : public Entity
{
private:
    float cooldown = 0;
    float shotspeed = 1.00;
    float projectilespeed = 180;

    int targetY = rand() % GetScene()->GetWindowHeight(); // Cible aléatoire pour Y
    float targetX = 0; // Cible pour X
    float movementSpeed = 100; // Vitesse de base

public:
    void OnCollision(Entity* other) override;
    void OnUpdate() override;
};
