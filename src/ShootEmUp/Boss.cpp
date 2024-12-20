#include "Camion.h"
#include "Projectile.h"
#include "GameScene.h"
#include <iostream>
#include "Player.h"
#include "Utils.h"
#include "Scene.h"
#include "Boss.h"
#include "Debug.h"
#include "GoFast.h"

void Boss::OnCollision(Entity* other)
{
    if (other->GetType() == EntityType::AllyProjectile) {
        hp--;
        other->Destroy();
    }
    if (hp < 1) {
        mToDestroy = true;
        pPlayer->AddScore(300);
    }
}

void Boss::OnUpdate()
{
    float windowWidth = GetScene()->GetWindowWidth();
    float windowHeight = GetScene()->GetWindowHeight();
    HandleCooldowns();

    if (hp <= 150 && phase == 1) {
        phase = 2;
    }

    if (atkPatternCooldown.IsReady()) {
        int randomAtk = rand() % 4 + 1;
        atkPatternCooldown.Reset();
        SpawnProjectilePattern(randomAtk);
    }

    if (movementPatternCooldown.IsReady()) {
        SpawnMovementPattern();
        movementPatternCooldown.Reset();
    }

    if (phase == 2) {
        sf::Color flash(255, 255, 255, 100);
        sf::Color flashscreen(255, 250, 235, 230);
        Debug::DrawFilledRectangle(0, GetPosition().y - GetHeight() / 3, windowWidth - (windowWidth - GetPosition().x), GetHeight(), flash);

        float px = pPlayer->GetPosition().x;
        float py = pPlayer->GetPosition().y;
        if (px < GetPosition().x && py < GetPosition().y + GetHeight() / 3 && py > GetPosition().y - GetHeight() / 2) {
            Debug::DrawFilledRectangle(0, 0, windowWidth, windowHeight, flashscreen);
            pPlayer->SetFlashed(true);
        }
        else {
            pPlayer->SetFlashed(false);
        }
    }
}

void Boss::SpawnProjectilePattern(int randomAtk)
{
    float playerX = pPlayer->GetPosition().x;
    float playerY = pPlayer->GetPosition().y;
    float windowHeight = GetScene()->GetWindowHeight();
    float windowWidth = GetScene()->GetWindowWidth();

    if (phase == 1) {
        switch (randomAtk) {
        case 1:
            for (int angle : {-20, -10, 0, 10, 20}) {
                GetScene<GameScene>()->AddProjectile(50, 30, GetPosition().x, GetPosition().y, "../../../res/Anim/ColisAnim/colis0.png", 4, 1, 0, GetPosition().y, EntityType::EnemyProjectile, angle, 200);
            }
            break;
        case 2:
            for (int angle : {-20, -15, -10, -5, 5, 10, 15, 20}) {
                int speed = (abs(angle) > 10) ? 130 : 120;
                GetScene<GameScene>()->AddProjectile(40, 30, GetPosition().x, GetPosition().y, "../../../res/Anim/ColisAnim/colis0.png", 4, 0.5, playerX, playerY, EntityType::EnemyProjectile, angle, speed);
            }
            break;
        case 3:
            for (int i = -180; i < 180; i += 10) {
                GetScene<GameScene>()->AddProjectile(30, 20, GetPosition().x, GetPosition().y, "../../../res/Anim/BriqueAnim/brique0.png", 4, 1, 0, GetPosition().y, EntityType::EnemyProjectile, i, 250);
            }
            for (int i = -180; i < 180; i += 15) {
                GetScene<GameScene>()->AddProjectile(50, 30, GetPosition().x, GetPosition().y, "../../../res/Anim/BriqueAnim/brique0.png", 4, 1, 0, GetPosition().y, EntityType::EnemyProjectile, i, 200);
            }
            for (int i = -180; i < 180; i += 20) {
                GetScene<GameScene>()->AddProjectile(70, 50, GetPosition().x, GetPosition().y, "../../../res/Anim/BriqueAnim/brique0.png", 4, 1, 0, GetPosition().y, EntityType::EnemyProjectile, i, 150);
            }
            break;
        case 4:
            //GetScene<GameScene>()->AddProjectile(90, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, EntityType::EnemyProjectile, 0, 160);
            int randomProj = rand() % 3 + 1;
            switch (randomProj)
            {
            case 1:
                GetScene<GameScene>()->AddProjectile(250, 220, GetPosition().x, GetPosition().y, "../../../res/Anim/BTPAnim/BTP0.png", 4, 1, playerX, playerY, EntityType::EnemyProjectile, 0, 160);
                break;
            case 2:
                GetScene<GameScene>()->AddProjectile(300, 200, GetPosition().x, GetPosition().y, "../../../res/Anim/CamionAnim/camion0.png", 4, 1, playerX, playerY, EntityType::EnemyProjectile, 0, 160);
                break;
            case 3:
                GetScene<GameScene>()->AddProjectile(200, 170, GetPosition().x, GetPosition().y, "../../../res/Anim/GoFastAnim/GoFast0.png", 4, 1, playerX, playerY, EntityType::EnemyProjectile, 0, 160);
                break;
            }
            break;
        }
    }
    else {
        switch (randomAtk) {
        case 1:
            GetScene<GameScene>()->CreateEntity<GoFast>("../../../res/Common/art/GoFast.png", 521 / 4, 296 / 4, EntityType::Enemy, 3)->SetPosition(0, rand() % static_cast<int>(windowHeight));
            break;
        case 2:
            for (int i = 0; i < 3; i++) {
                GetScene<GameScene>()->CreateEntity<GoFast>("../../../res/Common/art/GoFast.png", 521 / 4, 296 / 4, EntityType::Enemy, 3)->SetPosition(0, rand() % static_cast<int>(windowHeight));
            }
            break;
        case 3:
            for (int i = -180; i < 180; i += 10) {
                GetScene<GameScene>()->AddProjectile(30, 20, GetPosition().x, GetPosition().y, "../../../res/Anim/BriqueAnim/brique0.png", 4, 1, 0, GetPosition().y, EntityType::EnemyProjectile, i, 250);
            }
            break;
        case 4:
            int randomProj = rand() % 3 + 1;
            switch (randomProj)
            {
            case 1:
                GetScene<GameScene>()->AddProjectile(250, 220, GetPosition().x, GetPosition().y, "../../../res/Anim/BTPAnim/BTP0.png", 4, 1, playerX, playerY, EntityType::EnemyProjectile, 0, 160);
                break;
            case 2:
                GetScene<GameScene>()->AddProjectile(300, 200, GetPosition().x, GetPosition().y, "../../../res/Anim/CamionAnim/camion0.png", 4, 1, playerX, playerY, EntityType::EnemyProjectile, 0, 160);
                break;
            case 3:
                GetScene<GameScene>()->AddProjectile(200, 170, GetPosition().x, GetPosition().y, "../../../res/Anim/GoFastAnim/GoFast0.png", 4, 1, playerX, playerY, EntityType::EnemyProjectile, 0, 160);
                break;
            }
            break;
        }
    }
}

void Boss::SpawnMovementPattern()
{
    float windowWidth = GetScene()->GetWindowWidth();
    float windowHeight = GetScene()->GetWindowHeight();

    int randomMove = rand() % 3 + 1;
    switch (randomMove) {
    case 1:
        GoToPosition(windowWidth * 0.8, windowHeight * 0.5, moveSpeed);
        targetY = windowHeight * 0.2;
        break;
    case 2:
        GoToPosition(windowWidth * 0.8, windowHeight * 0.7, moveSpeed);
        targetY = windowHeight * 0.5;
        break;
    case 3:
        GoToPosition(windowWidth * 0.8, windowHeight * 0.35, moveSpeed);
        targetY = windowHeight * 0.8;
        break;
    }
}

void Boss::HandleCooldowns()
{
    float deltaTime = GetDeltaTime();
    atkPatternCooldown.Update(deltaTime);
    movementPatternCooldown.Update(deltaTime);
}
