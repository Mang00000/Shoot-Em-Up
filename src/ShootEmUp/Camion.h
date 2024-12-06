#pragma once
#include "Entity.h"
class GameScene;

class Camion : public Entity
{
private:
	float cooldown = 0;
	float shotspeed = 2;
	float projectilespeed = 180;
	int shotnum = 1;
	GameScene* pGM;
public:
	Camion();
	void OnCollision(Entity* other) override;

	void OnUpdate() override;
};

