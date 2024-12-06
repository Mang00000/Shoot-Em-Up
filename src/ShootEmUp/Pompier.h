#pragma once
#include "Entity.h"
class GameScene;

class Pompier : public Entity
{
private:
	float cooldown = 0;
	float shotspeed = 0.15;
	float projectilespeed = 180;
	GameScene* pGM;
public:
	Pompier();
	void OnCollision(Entity* other) override;

	void OnUpdate() override;
};

