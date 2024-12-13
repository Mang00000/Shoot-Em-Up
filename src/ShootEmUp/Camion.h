#pragma once
#include "Entity.h"

class Camion : public Entity
{
private:
	float cooldown = 0;
	float shotspeed = 2;
	float projectilespeed = 180;
	int shotnum = 1;
	float speed=100.0f;

public:
	void OnCollision(Entity* other) override;

	void OnUpdate() override;
};

