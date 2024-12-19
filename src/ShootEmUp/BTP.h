#include "Entity.h"
#include "Cooldown.h"
#include <vector>

class Projectile;

class BTP : public Entity {
private:
    Cooldown shootCooldown = Cooldown(5.0f); // Temps de recharge pour les tirs (5 secondes)
    float projectilespeed = 180;
    int hp = 10;
    float randomX = (rand() % 30) / 100.0f + 0.6f;

public:
    Player* pPlayer = GetScene<GameScene>()->GetPlayer();
    void OnCollision(Entity* other) override;
    void OnUpdate() override;
};
