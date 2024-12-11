#include "Entity.h"
#include <vector>
#include "Projectile.h"


class BTP : public Entity
{
private:
	float cooldown = 0;
	float shotspeed = 2.0;
	float projectilespeed = 180;
	bool isShooting = false;

public:
	void OnCollision(Entity* other) override;

	void OnUpdate() override;
};

