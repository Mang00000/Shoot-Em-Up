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
    if (other->IsTag("PlayerProj")) {
        hp--;
        other->Destroy();
    }
    if (hp < 1) {
        mToDestroy = true;
        pPlayer->AddScore(5);
    }
}
void Pompier::OnUpdate()
{
    float windowWidth = GetScene()->GetWindowWidth();
    float playerX = pPlayer->GetPosition().x;
    float playerY = pPlayer->GetPosition().y;

    if (cooldown > shotspeed) {
        GetScene<GameScene>()->AddProjectile(3, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 0, projectilespeed);
        cooldown = 0;
    }
    else {
        cooldown += GetDeltaTime();
    }

    if (std::abs(targetX - GetPosition().x) < 5.0f) {
        targetX = 0.8f + static_cast<float>(rand()) / RAND_MAX * 0.2f; 
        targetX *= windowWidth; 
    }

    float xDelta = targetX - GetPosition().x;
    float xSpeed = std::clamp(std::abs(xDelta) * 2.0f, 10.0f, 50.0f); 
    float newX = GetPosition().x + (xDelta > 0 ? xSpeed : -xSpeed) * GetDeltaTime(); 

    if (std::abs(targetY - GetPosition().y) < 5.0f) {
        targetY = rand() % GetScene()->GetWindowHeight();
    }

    float yDelta = targetY - GetPosition().y;
    float ySpeed = std::clamp(std::abs(yDelta) * 2.0f, 10.0f, 50.0f); 
    float newY = GetPosition().y + (yDelta > 0 ? ySpeed : -ySpeed) * GetDeltaTime(); 

    SetPosition(newX, newY);
}
