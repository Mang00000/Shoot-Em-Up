#pragma once
#include "Entity.h"
#include "Cooldown.h"

class Pompier : public Entity {
private:
    Cooldown shootCooldown = Cooldown(1.0f); 
    float projectilespeed = 180;

    int targetY = 200 + (rand() % (720 - 200));
    float targetX = 0; 
    float movementSpeed = 100; 
    int hp = 5;

    float randomX = (rand() % 30) / 100.0f + 0.6f;

public:
    Player* pPlayer = GetScene<GameScene>()->GetPlayer();
    void OnCollision(Entity* other) override;
    void OnUpdate() override;
};
