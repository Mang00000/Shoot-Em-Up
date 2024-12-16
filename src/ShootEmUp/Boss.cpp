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
    if (other->IsTag("PlayerProj")) {
        hp--;
        other->Destroy();
    }
    if (hp < 1) {
        mToDestroy = true;
    }
}

void Boss::OnUpdate()
{
    float windowWidth = GetScene()->GetWindowWidth();
    float windowHeight = GetScene()->GetWindowHeight();
    HandleCooldowns();
    if (hp <= 150 && phase == 1) {
        phase=2;
    }

    if (atkPatternCooldown.IsReady()) {
        int randomAtk = rand() % 4 + 1;
        Player* pPlayer = GetScene<GameScene>()->GetPlayer();
        float playerX = pPlayer->GetPosition().x;
        float playerY = pPlayer->GetPosition().y;
        //system("cls");
        //std::cout << "Hp: " << hp << "\nPhase: " << phase << "\nPattern: " << randomAtk << std::endl;
        atkPatternCooldown.Reset();
        if (phase == 1) {
            if (randomAtk == 1) {
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 0, 150 * 3);
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 10, 150 * 3);
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -10, 150 * 3);
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 20, 150 * 3);
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -20, 150 * 3);

            }
            else if (randomAtk == 2) {

                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 0, 130);

                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 10, 130);
                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -10, 130);
                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 20, 130);
                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -20, 130);

                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 15, 120);
                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -15, 120);
                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 5, 120);
                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -5, 120);


                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 10, 130 * 2);
                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -10, 130 * 2);
                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 20, 130 * 2);
                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -20, 130 * 2);

                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 15, 120 * 2);
                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -15, 120 * 2);
                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 5, 120 * 2);
                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -5, 120 * 2);

            }
            else if (randomAtk == 3) {
                for (int i = -180; i < 180; i += 10) {
                    GetScene<GameScene>()->AddProjectile(6, GetPosition().x, GetPosition().y, sf::Color::Blue, 0, 0, i, 250);
                }
                for (int i = -180; i < 180; i += 15) {
                    GetScene<GameScene>()->AddProjectile(8, GetPosition().x, GetPosition().y, sf::Color::Blue, 0, 0, i, 200);
                }
                for (int i = -180; i < 180; i += 20) {
                    GetScene<GameScene>()->AddProjectile(12, GetPosition().x, GetPosition().y, sf::Color::Blue, 0, 0, i, 150);
                }
                for (int i = -180; i < 180; i += 25) {
                    GetScene<GameScene>()->AddProjectile(16, GetPosition().x, GetPosition().y, sf::Color::Blue, 0, 0, i, 100);
                }
                for (int i = -180; i < 180; i += 30) {
                    GetScene<GameScene>()->AddProjectile(20, GetPosition().x, GetPosition().y, sf::Color::Blue, 0, 0, i, 50);
                }
            }
            else {

                GetScene<GameScene>()->AddProjectile(90, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 0, 160);

            }
        }
        else {
            int randomAtk = rand() % 4 + 1;
            if (randomAtk == 1) {
                int randY = rand() % static_cast<int>(windowHeight);
                Entity* newEnemy = nullptr;
                newEnemy = CreateEntity<GoFast>(60, sf::Color::Yellow);
                newEnemy->SetPosition(0, randY);
                newEnemy->SetTag("Enemy");
            }
            else if (randomAtk == 2) {
                for (int i = 0; i < 3; i++) {
                    int randY = rand() % static_cast<int>(windowHeight);
                    Entity* newEnemy = nullptr;
                    newEnemy = CreateEntity<GoFast>(60, sf::Color::Yellow);
                    newEnemy->SetPosition(0, randY);
                    newEnemy->SetTag("Enemy");
                }
            }
            if (randomAtk == 3) {
                for (int i = -180; i < 180; i += 10) {
                    GetScene<GameScene>()->AddProjectile(6, GetPosition().x, GetPosition().y, sf::Color::Blue, 0, 0, i, 250);
                }
                for (int i = -180; i < 180; i += 15) {
                    GetScene<GameScene>()->AddProjectile(8, GetPosition().x, GetPosition().y, sf::Color::Blue, 0, 0, i, 200);
                }
                for (int i = -180; i < 180; i += 20) {
                    GetScene<GameScene>()->AddProjectile(12, GetPosition().x, GetPosition().y, sf::Color::Blue, 0, 0, i, 150);
                }
                for (int i = -180; i < 180; i += 25) {
                    GetScene<GameScene>()->AddProjectile(16, GetPosition().x, GetPosition().y, sf::Color::Blue, 0, 0, i, 100);
                }
                for (int i = -180; i < 180; i += 30) {
                    GetScene<GameScene>()->AddProjectile(20, GetPosition().x, GetPosition().y, sf::Color::Blue, 0, 0, i, 50);
                }
            }
            if (randomAtk == 4) {
                GetScene<GameScene>()->AddProjectile(90, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 0, 160);
            }

        }   
    }
    if (movementPatternCooldown.IsReady()) {
        int randomMove = rand() % 3 + 1;

        if (randomMove == 1) {
            GoToPosition(windowWidth * 0.8, windowHeight * 0.2,moveSpeed);
            targetY = windowHeight * 0.2;
        }
        if (randomMove == 2) {
            GoToPosition(windowWidth * 0.8, windowHeight * 0.5, moveSpeed);
            targetY = windowHeight * 0.5;
        }
        if (randomMove == 3) {
            GoToPosition(windowWidth * 0.8, windowHeight * 0.8, moveSpeed);
            targetY = windowHeight * 0.8;
        }
        movementPatternCooldown.Reset();
    }
    if (phase == 2) {
        sf::Color flash(255, 255, 255,100);
        sf::Color flashscreen(255, 250, 235, 230);
        Debug::DrawFilledRectangle(0, GetPosition().y - GetHeight()/2, windowWidth - (windowWidth - GetPosition().x), GetHeight(), flash);
        Player* pPlayer = GetScene<GameScene>()->GetPlayer();
        float px = pPlayer->GetPosition().x;
        float py = pPlayer->GetPosition().y;
        if (px < GetPosition().x && py < GetPosition().y + GetHeight() / 2 && py > GetPosition().y - GetHeight() / 2) {
            Debug::DrawFilledRectangle(0,0, windowWidth,windowHeight, flashscreen);
            pPlayer->SetFlashed(true);
        }
        else {
            pPlayer->SetFlashed(false);
        }
    }
}
void Boss::HandleCooldowns() {
    float deltaTime = GetDeltaTime();
    atkPatternCooldown.Update(deltaTime);
    movementPatternCooldown.Update(deltaTime);
}