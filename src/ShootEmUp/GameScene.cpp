#include "GameScene.h"

#include "Camion.h"
#include "Projectile.h"
#include "Player.h"
#include "GoFast.h"
#include "BTP.h"
#include "Pompier.h"
#include "Boss.h"

#include "Debug.h"

#include <iostream>

#include <stdlib.h>

#include "Utils.h" 
#include "Scene.h"
void GameScene::OnInitialize()
{
    pPlayer = CreateEntity<Player>(20, sf::Color::Green);
    pPlayer->SetPosition(100, 500);
    pPlayer->SetTag("Player");

    std::srand(static_cast<unsigned>(std::time(nullptr))); 
    GenerateEnemies(5); 
}

void GameScene::OnEvent(const sf::Event& event)
{
    if ((event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) && pPlayer != nullptr) {
        bool isMovingUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        bool isMovingDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
        bool isMovingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        bool isMovingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

        bool isSlowed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
        bool isClear = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
        bool isFlashing = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        bool isKlaxoning = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
        bool isRocketLauncher = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

        float speed = isSlowed ? 400.0f / 3.0f : 400.0f;
        float deltaTime = GetDeltaTime();

        float moveX = 0.0f;
        float moveY = 0.0f;
        float radius = 0;

        if (isMovingUp)    moveY -= 1.0f;
        if (isMovingDown)  moveY += 1.0f;
        if (isMovingLeft)  moveX -= 1.0f;
        if (isMovingRight) moveX += 1.0f;

        if (isKlaxoning) pPlayer->Klaxon();
        if (isFlashing) pPlayer->Flashing();
        if (isRocketLauncher) pPlayer->Rocket();
        if (isClear) ClearEntity(2);

        if (moveX != 0.0f || moveY != 0.0f ) {
            sf::Vector2f direction(moveX, moveY);
            if (Utils::Normalize(direction)) {
                pPlayer->SetDirection(direction.x, direction.y, speed); // Mouvement
            }
                
        }
        else {
            pPlayer->SetSpeed(0); pPlayer->SetDirection(0, 0); // Stopper le mouvement
        }                    
    }
}
#include <cstdlib>
#include <ctime>

void GameScene::GenerateEnemies(int count, int maxGoFast, int maxPompier, int maxCamion, int maxBTP)
{
    float screenWidth = GetWindowWidth();
    float screenHeight = GetWindowHeight();

    ClearEntity(2);

    int goFastCount = 0;
    int pompierCount = 0;
    int camionCount = 0;
    int btpCount = 0;

    if (wave == 2) {
        Entity* boss= nullptr;
        boss = CreateEntity<Boss>(90, sf::Color::White);
        pEnemies.push_back(boss);
        float x = 800;
        float y = 400;
        boss->SetPosition(x, y);
        boss->SetTag("Enemy");

        Entity* bos2s = nullptr;
        bos2s = CreateEntity<Boss>(90, sf::Color::White);
        pEnemies.push_back(bos2s);
        x = 700;

        bos2s->SetPosition(x, y);
        bos2s->SetTag("Enemy");

        Entity* b1os2s = nullptr;
        b1os2s = CreateEntity<Boss>(90, sf::Color::White);
        pEnemies.push_back(b1os2s);
        x = 700;

        b1os2s->SetPosition(x, y);
        b1os2s->SetTag("Enemy");
        return;
    }

    for (int i = 0; i < count; ++i) {
        if (goFastCount >= maxGoFast && pompierCount >= maxPompier && camionCount >= maxCamion && btpCount >= maxBTP) {
            break; 
        }

        float x = screenWidth * 0.8f + static_cast<float>(std::rand() % static_cast<int>(screenWidth * 0.2f));
        float y = static_cast<float>(std::rand() % static_cast<int>(screenHeight));

        Entity* newEnemy = nullptr;
        int enemyType = std::rand() % 4;

        switch (enemyType) {
        case 0:
            if (goFastCount < maxGoFast) {
                newEnemy = CreateEntity<GoFast>(60, sf::Color::Yellow);
                goFastCount++;
            } 
            break;
        case 1:
            if (pompierCount < maxPompier) {
                newEnemy = CreateEntity<Pompier>(30, sf::Color::Red);
                pompierCount++;
            }
            break;
        case 2:
            if (camionCount < maxCamion) {
                newEnemy = CreateEntity<Camion>(40, sf::Color::Blue);
                camionCount++;
            }
            break;
        case 3:
            if (btpCount < maxBTP) {
                newEnemy = CreateEntity<BTP>(30, sf::Color::Green);
                btpCount++;
            }
            break;
        }

        if (newEnemy) {
            newEnemy->SetPosition(x, y);
            newEnemy->SetTag("Enemy");
            pEnemies.push_back(newEnemy);
        }
    }
}



void GameScene::OnUpdate()
{

    Debug::DrawText(50, 50, "Vague: " + std::to_string(wave), sf::Color::White);
    if (pPlayer->GetIsDead()) {
        running = false;
        RemoveProjectile("PlayerProj");
        RemoveProjectile("EnemyProj");
        ClearEntity(2);
        ClearEntity(1);
        Debug::DrawText(GetWindowWidth() / 2, GetWindowHeight() / 2, "PERDU", sf::Color::White);
        pPlayer->Destroy();
    }

    sf::Vector2i mousePos = sf::Mouse::getPosition(*GetRenderWindow());
    Debug::DrawCircle(mousePos.x, mousePos.y, 7, sf::Color::White);

    pEnemies.erase(std::remove_if(pEnemies.begin(), pEnemies.end(),
        [](Entity* enemy) { return enemy->ToDestroy(); }), pEnemies.end());

    if (pEnemies.empty() && running) {
        RemoveProjectile("EnemyProj");
        GenerateEnemies(4 + wave, 4 /*maxGoFast*/ );
        wave++;
        pPlayer->SetFlashed(false);
    }

    for (auto it = pProjectile.begin(); it != pProjectile.end(); ) {
        if ((*it)->ToDestroy()) {
            it = pProjectile.erase(it); 
        }
        else {
            ++it;
        }
    }
}

Player* GameScene::GetPlayer()
{
    return pPlayer;
}

void GameScene::AddProjectile(int size, float x, float y, sf::Color color, float dx, float dy, float angle, float speed, std::string tag) {
    Entity* p = nullptr;
    p = CreateEntity<Projectile>(size, color);
    p->SetPosition(x, y);
    p->GoToDirection(dx, dy, speed);
    p->SetTag(tag);
    p->RotateDirection(angle);
    pProjectile.push_back(p);
}
void GameScene::AddGuidedProjectile(int size, float x, float y, sf::Color color,float speed,std::string tag, Entity* target,float Vx0, float Vy0) {
    if (Vx0 == -1) Vx0 = x;
    GuidedProjectile* p = nullptr;
    p = CreateEntity<GuidedProjectile>(size, color);
    p->SetTarget(target);
    p->SetPosition(x, y);
    p->GoToDirection(Vx0, Vy0, speed);

    p->SetTag(tag);
    pProjectile.push_back(p);
}
void GameScene::RemoveProjectile(std::string tag) {

    for (Entity* projectile : pProjectile) {
        if (projectile->IsTag(tag)) {
            projectile->Destroy();
        }
    }
}
Entity* GameScene::GetClosestEnemy(Entity* fromWho) {
    float closestDistance = 99999;
    Entity* closestEntity = nullptr;

    for (Entity* enemy : pEnemies) {
        float newDistance = Utils::GetDistance(enemy->GetPosition().x, enemy->GetPosition().y, fromWho->GetPosition().x, fromWho->GetPosition().y);
        if (newDistance < closestDistance) {
            closestDistance = newDistance;
            closestEntity = enemy;
        }
    }
    return closestEntity;
}
sf::Vector2f GameScene::GetEntityPosition(Entity* entity, float ratioX, float ratioY) const {
    if (!entity->ToDestroy()) {
        return entity->GetPosition(ratioX, ratioY);
    }
    else {
        return { -1,-1 };
    }
}
void GameScene::ClearEntity(int team) {
    if (team == 2) {
        for (Entity* enemy : pEnemies) {
            enemy->Destroy();
        }
        pEnemies.clear();
    }
    else if (team == 1) {

    }

}