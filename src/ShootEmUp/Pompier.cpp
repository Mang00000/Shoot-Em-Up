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
	Player* pPlayer = GetScene<GameScene>()->GetPlayer();
	int x = pPlayer->GetPosition().x;
	int y = pPlayer->GetPosition().y;
	if (cooldown > shotspeed) {

		GetScene<GameScene>()->AddProjectile(3, GetPosition().x, GetPosition().y, sf::Color::Blue, x, y, 0, projectilespeed);

		cooldown = 0;
	}
	else {
		cooldown += GetDeltaTime();
	}


}