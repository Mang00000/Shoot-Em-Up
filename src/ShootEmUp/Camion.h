#pragma once
#include "Entity.h"
class GameScene;

class Camion : public Entity
{
private:
	float cooldown = 0;
	float shotspeed = 0.15;
	float projectilespeed = 1380;
	GameScene* pGM;
public:
	Camion();
	void OnCollision(Entity* other) override;

	void OnUpdate() override;
};

