#include "Entity.h"
#include <vector>
#include "Projectile.h"


class BTP : public Entity
{
private:
	float cooldown = 0;
	float shotspeed = 5.0;
	float projectilespeed = 180;
	bool isShooting = false;
	int hp = 10;
	float randomX = (rand() % 30) / 100.0f + 0.6f;

public:
	Player* pPlayer = GetScene<GameScene>()->GetPlayer();
	void OnCollision(Entity* other) override;

	void OnUpdate() override;
};

