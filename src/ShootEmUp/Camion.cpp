#include "Camion.h"
#include "Projectile.h"
#include "GameScene.h"
#include <iostream>
#include "Player.h"
#include <random>

Camion::Camion()
{
	pGM = this->GetScene<GameScene>();
}

void Camion::OnCollision(Entity* other)
{
}

void Camion::OnUpdate()
{
	Player* pPlayer = pGM->GetPlayer();
	int x = pPlayer->GetPosition().x;
	int y = pPlayer->GetPosition().y;
	if (cooldown > shotspeed) {	
		for (int i = 1; i <= shotnum; i++) {
			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<std::mt19937::result_type> distPos(6, 14);

			float randPos = distPos(rng) / 10.00f;

			Projectile* p = GetScene()->CreateEntity<Projectile>(15, sf::Color::Magenta);
			p->SetPosition(GetPosition().x, GetPosition().y);
			p->GoToDirection(x * randPos, y * randPos, projectilespeed);
		}
		cooldown = 0;
		shotnum = rand() % 3;
	}
	else {

		cooldown += GetDeltaTime();
	}
}