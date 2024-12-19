#include "Camion.h"
#include "Projectile.h"
#include "GameScene.h"
#include <iostream>
#include "Player.h"
#include "Utils.h"
#include "Scene.h"

void Camion::OnCollision(Entity* other) {
    if (other->GetType() == EntityType::AllyProjectile) {
        hp--;
        other->Destroy();
    }
    if (hp < 1) {
        mToDestroy = true;
        pPlayer->AddScore(5);
    }
}

void Camion::OnUpdate() {
    float windowWidth = GetScene()->GetWindowWidth();

  
    shootCooldown.Update(GetDeltaTime());

  
    if (shootCooldown.IsReady()) {
        for (int i = 1; i <= shotnum; i++) {
            int randangle = (rand() % 180) - 90; 
            GetScene<GameScene>()->AddProjectile(15, GetPosition().x, GetPosition().y, sf::Color::Magenta, 0, GetPosition().y, EntityType::EnemyProjectile, randangle, projectilespeed);
        }

        shootCooldown.Reset();
        shotnum = (rand() % 3) + 1;         
        shootCooldown.maxTime = (rand() % 30 + 1) / 10.0f; 
    }

    speed = std::abs(pPlayer->GetPosition().y - GetPosition().y) / 2.0f;

    GoToDirection(windowWidth * randomX, pPlayer->GetPosition().y, speed);
}
