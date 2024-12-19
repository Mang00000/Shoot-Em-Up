#pragma once
#include "Entity.h"
#include "Cooldown.h"

class Camion : public Entity {
private:
    Cooldown shootCooldown = Cooldown(2.0f);
    float projectilespeed = 180;
    int shotnum = 1;
    float speed = 100.0f;
    int hp = 8;

    float randomX = (rand() % 30) / 100.0f + 0.6f;

public:
    Player* pPlayer = GetScene<GameScene>()->GetPlayer();
    void OnCollision(Entity* other) override;
    void OnUpdate() override;
};
