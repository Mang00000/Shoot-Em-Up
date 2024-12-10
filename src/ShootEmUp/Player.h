#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
	float cooldown = 0;
	float shotspeed = 1.00;
	float projectilespeed = 580;
	int hp = 3;
	int projectilesize = 3;
	bool buffSpeed = false;
	bool buffSize = false;

	float invicibleCooldown = 0.0f;
	float invicibleTime = 3.0f;
	bool isInvicible = true;

	float flashCooldown = 0.0f;
	float flashTime = 3.0f;
	bool isFlashing = false;
	float flashingCooldown = 0.0f;
	float flashingTime = 1.0f;

	float klaxonCooldown = 0.0f;
	float klaxonTime = 12.0f;
public:
	void OnCollision(Entity* other) override;

	void OnUpdate() override;
	void Klaxon();
	void Flashing();
};

