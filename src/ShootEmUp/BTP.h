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

public:
	void OnCollision(Entity* other) override;

	void OnUpdate() override;
};

