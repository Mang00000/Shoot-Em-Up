#include "Pompier.h"
#include "Projectile.h"
#include "GameScene.h"
#include <iostream>
#include "Player.h"

Pompier::Pompier()
{
	pGM = this->GetScene<GameScene>();
}

void Pompier::OnCollision(Entity* other)
{
}


void Pompier::OnUpdate()
{
	Player* pPlayer = pGM->GetPlayer();
	int x = pPlayer->GetPosition().x;
	int y = pPlayer->GetPosition().y;
	if (cooldown > shotspeed) {
		Projectile* p = GetScene()->CreateEntity<Projectile>(3, sf::Color::Blue);
		p->SetPosition(GetPosition().x, GetPosition().y);
		p->GoToDirection(x, y, projectilespeed);
		cooldown = 0;
	}
	else {
		cooldown += GetDeltaTime();
	}


}