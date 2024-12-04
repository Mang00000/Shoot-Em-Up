#include "Camion.h"
#include "Projectile.h"
#include "GameScene.h"
#include <iostream>
#include "Player.h"

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
		Projectile* p = GetScene()->CreateEntity<Projectile>(5, sf::Color::Red);
		p->SetPosition(GetPosition().x, GetPosition().y);
		p->GoToDirection(x, y, projectilespeed);

		Projectile* p2 = GetScene()->CreateEntity<Projectile>(5, sf::Color::Red);
		p2->SetPosition(GetPosition().x, GetPosition().y);
		p2->GoToDirection(x-20, y-20, projectilespeed);

		Projectile* p3 = GetScene()->CreateEntity<Projectile>(5, sf::Color::Red);
		p3->SetPosition(GetPosition().x, GetPosition().y);
		p3->GoToDirection(x+20, y+20, projectilespeed);

		Projectile* p4 = GetScene()->CreateEntity<Projectile>(5, sf::Color::Red);
		p4->SetPosition(GetPosition().x, GetPosition().y);
		p4->GoToDirection(x - 50, y - 50, projectilespeed);

		Projectile* p5 = GetScene()->CreateEntity<Projectile>(5, sf::Color::Red);
		p5->SetPosition(GetPosition().x, GetPosition().y);
		p5->GoToDirection(x + 50, y + 50, projectilespeed);
		cooldown = 0;
	}
	else {
		cooldown += GetDeltaTime();
	}


}