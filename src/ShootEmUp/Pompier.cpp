#include "Pompier.h"
#include "Projectile.h"
#include "GameScene.h"
#include <iostream>
#include "Player.h"

void Pompier::OnCollision(Entity* other)
{
	if (other->IsTag(1)) {
		mToDestroy = true;
		other->Destroy();
	}
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
		p->SetTag(2);
		cooldown = 0;
	}
	else {
		cooldown += GetDeltaTime();
	}


}