#include "Projectile.h"
#include "Scene.h"
#include <iostream>
#include <random>
#include "GameScene.h"
#include "Player.h"

void Projectile::OnCollision(Entity* other)
{
}


void Projectile::OnUpdate()
{
	if (GameScene::IsPaused == false)
	{
		float x = GetPosition().x;
		float y = GetPosition().y;
		float r = GetWidth();
		float h = GetScene()->GetWindowHeight();
		float w = GetScene()->GetWindowWidth();

		if (x - r < 0 || y - r < 0 || x + r > w || y + r > h) mToDestroy = true;
	}
}

ProjectileCamion::ProjectileCamion() 
{
	if (GameScene::IsPaused == false || GameScene::isGameStart == true) 
	{
		Player* pPlayer = pGM->GetPlayer();
		int x = pPlayer->GetPosition().x;
		int y = pPlayer->GetPosition().y;

		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_real_distribution<float> distAngle(-90.0f, 90.0f);

		float randomAngleDegrees = distAngle(rng);

		GoToDirection(x, y, 180);
		SetTag(2);
		RotateDirection(randomAngleDegrees);
	}
}
void ProjectileCamion::OnCollision(Entity* other)
{
}
void ProjectileCamion::OnUpdate()
{
	if (GameScene::IsPaused == false)
	{
		float x = GetPosition().x;
		float y = GetPosition().y;
		float r = GetWidth();
		float h = GetScene()->GetWindowHeight();
		float w = GetScene()->GetWindowWidth();

		if (x - r < 0 || y - r < 0 || x + r > w || y + r > h) mToDestroy = true;
	}
}