#include "Camion.h"
#include "Projectile.h"
#include "GameScene.h"
#include <iostream>
#include "Player.h"
#include <random>
#include "Utils.h"
void Camion::OnCollision(Entity* other)
{
	if (other->IsTag(1)) {
		mToDestroy = true;
		other->Destroy();
	}
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
            std::uniform_real_distribution<float> distAngle(-90.0f, 90.0f);

            float randomAngleDegrees = distAngle(rng);


            Projectile* p = GetScene()->CreateEntity<Projectile>(15, sf::Color::Magenta);
            p->SetPosition(GetPosition().x, GetPosition().y);
            p->GoToDirection(0, p->GetPosition().y, projectilespeed);
            p->RotateDirection(randomAngleDegrees);
            p->SetTag(2);
        }

        cooldown = 0;

        shotnum = (rand() % 3) + 1;
        shotspeed = (rand() % 30 + 1)/10;
    }
    else {
        cooldown += GetDeltaTime();
    }
}
