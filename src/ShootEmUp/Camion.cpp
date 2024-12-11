#include "Camion.h"
#include "Projectile.h"
#include "GameScene.h"
#include <iostream>
#include "Player.h"
#include "Utils.h"
#include "Scene.h"
void Camion::OnCollision(Entity* other)
{
	if (other->IsTag(1)) {
		mToDestroy = true;
		other->Destroy();
	}
}

void Camion::OnUpdate()
{
    if (cooldown > shotspeed) {
        for (int i = 1; i <= shotnum; i++) {
            int randangle = (rand() % 180) - 90;
            GetScene<GameScene>()->AddProjectile(15, GetPosition().x, GetPosition().y, sf::Color::Magenta, 0, GetPosition().y, randangle, projectilespeed);

        }

        cooldown = 0;

        shotnum = (rand() % 3) + 1;
        shotspeed = (rand() % 30 + 1)/10;
    }
    else {
        cooldown += GetDeltaTime();
    }
}
