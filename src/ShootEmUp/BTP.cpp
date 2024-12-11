#include "BTP.h"
#include "Projectile.h"
#include <iostream>
#include "Player.h"
#include "Utils.h" 

void BTP::OnCollision(Entity* other)
{
    if (other->IsTag(1)) {
        mToDestroy = true;
        other->Destroy();
    }
}

void BTP::OnUpdate()
{
    Player* pPlayer = pGM->GetPlayer();
    int x = pPlayer->GetPosition().x;
    int y = pPlayer->GetPosition().y;

    if (cooldown > shotspeed) {
        Projectile* p = GetScene()->CreateEntity<Projectile>(8, sf::Color::Red);
        p->SetPosition(GetPosition().x, GetPosition().y);
        p->GoToDirection(x, y, projectilespeed);
        p->SetTag(2);

        cooldown = 0; 
    }
    cooldown += GetDeltaTime();
}


