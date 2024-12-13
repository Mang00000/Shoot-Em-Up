#include "Pompier.h"
#include "Projectile.h"
#include "GameScene.h"
#include <iostream>
#include "Player.h"
#include "Scene.h"
#include "Entity.h"
#include <cmath>

void Pompier::OnCollision(Entity* other)
{
    if (other->IsTag(1)) {
        hp--;
        other->Destroy();
    }
    if (hp < 1) {
        mToDestroy = true;
    }
}

void Pompier::OnUpdate()
{
    Player* pPlayer = GetScene<GameScene>()->GetPlayer();
    float playerX = pPlayer->GetPosition().x;
    float playerY = pPlayer->GetPosition().y;

    if (cooldown > shotspeed) {
        GetScene<GameScene>()->AddProjectile(3, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 0, projectilespeed);
        cooldown = 0;
    }
    else {
        cooldown += GetDeltaTime();
    }

    float windowWidth = GetScene()->GetWindowWidth();

    if (std::abs(targetX - GetPosition().x) < 5.0f) {
        targetX = windowWidth * (0.8f + static_cast<float>(rand()) / RAND_MAX * 0.2f); 
    }

    float xDelta = targetX - GetPosition().x;
    float xSpeed = std::clamp(std::abs(xDelta) * 2.0f, 10.0f, 50.0f); 
    float newX = GetPosition().x;

    if (std::abs(targetY - GetPosition().y) < 5.0f) {
        targetY = rand() % GetScene()->GetWindowHeight(); 
    }

    float yDelta = targetY - GetPosition().y;
    float ySpeed = std::clamp(std::abs(yDelta) * 2.0f, 10.0f, 50.0f);
    float newY = GetPosition().y + (yDelta > 0 ? ySpeed : -ySpeed) * GetDeltaTime();

    SetPosition(newX, newY);
}
