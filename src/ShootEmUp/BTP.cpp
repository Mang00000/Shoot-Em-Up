#include "BTP.h"
#include "Projectile.h"
#include <iostream>
#include "Player.h"
#include "Utils.h"

void BTP::OnCollision(Entity* other) {
    if (other->GetType() == EntityType::AllyProjectile) {
        hp--;
        other->Destroy();
    }
    if (hp < 1) {
        mToDestroy = true;
        pPlayer->AddScore(5);
    }
}

void BTP::OnUpdate() {
    float windowWidth = GetScene()->GetWindowWidth();
    int x = pPlayer->GetPosition().x;
    int y = pPlayer->GetPosition().y;

    // Mise à jour du cooldown
    shootCooldown.Update(GetDeltaTime());

    // Tir si prêt
    if (shootCooldown.IsReady()) {
        GetScene<GameScene>()->AddGuidedProjectile(7, GetPosition().x, GetPosition().y, sf::Color::Red, projectilespeed, EntityType::EnemyProjectile, GetScene<GameScene>()->GetPlayer(), x, y);
        shootCooldown.Reset();
    }

    // Déplacement
    GoToPosition(windowWidth * randomX, GetPosition().y, 100);
}
