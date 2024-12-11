#pragma once
#include "Entity.h"

class Pompier : public Entity
{
private:
	float cooldown = 0;
	float shotspeed = 1.00;
	float projectilespeed = 180;
	int targetY = rand() % GetScene()->GetWindowHeight();
public:
	void OnCollision(Entity* other) override;

	void OnUpdate() override;
};

