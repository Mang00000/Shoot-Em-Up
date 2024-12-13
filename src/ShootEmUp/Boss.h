#pragma once
#include "Entity.h"

class Boss : public Entity
{
private:
	int hp = 300;
	Cooldown movementPatternCooldown{ 6.0f };
	Cooldown atkPatternCooldown{ 4.0f };
	Cooldown atkCooldown{ 0.2f };


public:
	void OnCollision(Entity* other) override;

	void OnUpdate() override;
	void HandleCooldowns();
};

