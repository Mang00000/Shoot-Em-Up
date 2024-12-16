#include "BTP.h"
#include "Projectile.h"
#include <iostream>
#include "Player.h"
#include "Utils.h" 

void BTP::OnCollision(Entity* other)
{
    if (other->IsTag("PlayerProj")) {
        hp--;
        other->Destroy();
    }
    if (hp < 1) {
        mToDestroy = true;
    }
}

void BTP::OnUpdate()
{
    Player* pPlayer = GetScene<GameScene>()->GetPlayer();
    int x = pPlayer->GetPosition().x;
    int y = pPlayer->GetPosition().y;

    if (cooldown > shotspeed) {
        GetScene<GameScene>()->AddGuidedProjectile(7, GetPosition().x, GetPosition().y, sf::Color::Red,projectilespeed, "EnemyProj", GetScene<GameScene>()->GetPlayer(),x,y);
        cooldown = 0; 
    }
    cooldown += GetDeltaTime();
}


