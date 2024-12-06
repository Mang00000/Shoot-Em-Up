#include "BTP.h"
#include "Projectile.h"
#include "GameScene.h"
#include <iostream>
#include "Player.h"

BTP::BTP()
{
	pGM = this->GetScene<GameScene>();
}

void BTP::OnCollision(Entity* other)
{
}


void BTP::OnUpdate()
{
	Player* pPlayer = pGM->GetPlayer();
	int x = pPlayer->GetPosition().x;
	int y = pPlayer->GetPosition().y;
	if (cooldown > shotspeed) {
		if (!isShooting) {
			Projectile* p = GetScene()->CreateEntity<Projectile>(8, sf::Color::Red);
			p->SetPosition(GetPosition().x, GetPosition().y);
			p->GoToDirection(x, y, projectilespeed);
			pList.push_back(p);
			isShooting = true;
		}
		else {
			projectileaimcooldown += GetDeltaTime();
			if (pList.empty()) {
				isShooting = false;
				cooldown = 0;
				std::cout << "no ball";
				return;
			}
			if (projectileaimcooldown < aimcooldown) return;
			for (auto* p : pList) {
				if (p->ToDestroy()) {
					pList.pop_back();
				}
				else {
					float py = p->GetPosition().y;
					float px = p->GetPosition().x;

					if (x > px) {
						p->GoToPosition(x, y, 200);
					}
					else {
						p->GoToPosition(GetScene()->GetWindowWidth(), y, 200);
					}

					system("cls");

				}
			}
			projectileaimcooldown = 0;
		}
	}
	else if (!isShooting) {
		cooldown += GetDeltaTime();
	}



}