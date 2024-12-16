#pragma once
#include "Entity.h"

class Boss : public Entity
{
private:
	int hp = 300;
	Cooldown movementPatternCooldown{ 6.0f };
	Cooldown atkPatternCooldown{ 4.2f };

	int phase = 1;
	float moveSpeed=150;
	float targetY = 0;


public:
	void OnCollision(Entity* other) override;

	void OnUpdate() override;
	void HandleCooldowns();
};

