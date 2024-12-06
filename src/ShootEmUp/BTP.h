#include "Entity.h"
#include <vector>
#include "Projectile.h"
class GameScene;

class BTP : public Entity
{
private:
	float cooldown = 0;
	float shotspeed = 0.15;
	float projectilespeed = 180;
	GameScene* pGM;
	bool isShooting = false;
	float projectileaimcooldown = 0;
	float aimcooldown = 0.05f;
public:
	std::vector<Projectile*> pList;
	BTP();
	void OnCollision(Entity* other) override;

	void OnUpdate() override;
};

