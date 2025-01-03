#include "GameScene.h"
#include "GameManager.h"
#include "Camion.h"
#include "Projectile.h"
#include "Player.h"
#include "GoFast.h"
#include "BTP.h"
#include "Pompier.h"
#include "Boss.h"
#include "Entity.h"
#include "Image.h"

#include "Debug.h"

#include <iostream>

#include <stdlib.h>

#include "Utils.h" 
#include "Scene.h"

#include <fstream>
#include <unordered_map>
#include <functional>
#include <vector>
#include <tuple>
#include "Collider.h"
#include "ResourceManager.h"

void GameScene::OnInitialize()
{
    //ResourceManager::Get()->LoadAllSounds("../../../res/sfx/");

    //pPlayer = CreateEntity<Player>("../../../res/TestAnim/monkey.png",20, sf::Color::Green, EntityType::Player);
    pPlayer = CreateEntity<Player>("../../../res/Anim/PlayerAnim/player0.png", 250/3, 417/3, 4, 1, EntityType::Player, 3);
    pPlayer->SetPosition(100, 500);

    std::srand(static_cast<unsigned>(std::time(nullptr))); 
    LoadWave("../../../res/Levels/level.txt");

    const int numImages = 11;
    const std::string basePath = "../../../res/Common/art2/";
    const std::string fileExtension = ".png";
    float parallaxValues[numImages] = { 1800, 1000, 200, 200, 200, 100, 100, 0, 0, 0, 0 }; // Parallax personnalis�es

    for (int i = numImages - 1; i >= 0; --i) // Boucle invers�e, 1.png = top 11.png = bottom
    {
        std::string filePath = basePath + std::to_string(i + 1) + fileExtension; // Charger 11.png, 10.png, ..., 1.png

        Image* assetRight = CreateEntity<Image>(filePath, 1280, 720, EntityType::Count, 0);
        assetRight->SetPosition(640, 360); 
        assetRight->SetParallax(parallaxValues[i]);

        Image* assetLeft = CreateEntity<Image>(filePath, 1280, 720, EntityType::Count, 0);
        assetLeft->SetPosition(-640, 360);
        assetLeft->SetParallax(parallaxValues[i]); 
    }

}

void GameScene::LoadWave(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Erreur d'ouverture du fichier : " << filename << std::endl;
        return;
    }


    std::unordered_map<int, std::tuple<std::function<Entity* ()>, sf::Color>> enemyMap;

    enemyMap[1] = { [this]() { return CreateEntity<GoFast>("../../../res/Common/art/GoFast.png",521/4,296/4, EntityType::Enemy,3); }, sf::Color::Yellow };
    enemyMap[2] = { [this]() { return CreateEntity<BTP>("../../../res/Common/art/BTP.png",670 / 4,395 / 4, EntityType::Enemy,3); }, sf::Color::Green };
    enemyMap[3] = { [this]() { return CreateEntity<Camion>("../../../res/Common/art/Camion.png",612 / 4,289 / 4, EntityType::Enemy,3); }, sf::Color::Blue };
    enemyMap[4] = { [this]() { return CreateEntity<Pompier>("../../../res/Common/art/Pompier.png",2062 / 12, 910 / 12, EntityType::Enemy,3); }, sf::Color::Red };
    enemyMap[5] = { [this]() { return CreateEntity<Boss>("../../../res/Common/art/Boss.png",1821 / 4,934 / 4, EntityType::Enemy,3); }, sf::Color::White };

    std::vector<int> positions = { 300, 400, 500, 600 };

    int checkwave = 1;

    int e1, e2, e3, e4;
    while (inFile >> e1 >> e2 >> e3 >> e4) {
        std::vector<int> enemies = { e1, e2, e3, e4 };
        for (size_t i = 0; i < enemies.size(); ++i) {
            if (enemies[i] == -1) {
                checkwave++;
            }
            if (checkwave == wave) {
                if (enemies[i] != 0) {
                    if (enemies[i] == 5) {
                        if (!mMusic.openFromFile("../../../res/Music/At the Speed of Light.wav"))
                            return; // error
                        mMusic.setVolume(5.f);
                        mMusic.play();
                    }
                    auto it = enemyMap.find(enemies[i]);
                    if (it != enemyMap.end()) {
                        auto [enemyCreator, color] = it->second;
                        Entity* newEnemy = enemyCreator();
                        newEnemy->SetPosition(GetWindowWidth()+newEnemy->GetWidth(), positions[i]);
                        pEnemies.push_back(newEnemy);
                    }
                }
            }
        }
    }

    inFile.close();
}



void GameScene::OnEvent(const sf::Event& event)
{
    if ((event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) && pPlayer != nullptr) {
        bool isMovingUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        bool isMovingDown = sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
        bool isMovingLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        bool isMovingRight = sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        bool pause = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

        bool isSlowed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);
        bool isClear = sf::Keyboard::isKeyPressed(sf::Keyboard::Enter);
        bool isFlashing = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
        bool isKlaxoning = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
        bool isRocketLauncher = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

        bool isDebug = sf::Keyboard::isKeyPressed(sf::Keyboard::X);

        float speed = isSlowed ? 400.0f / 3.0f : 400.0f;

        float moveX = 0.0f;
        float moveY = 0.0f;
        float radius = 0;

        if (pause) {
            GameManager::Get()->Pause();
        }

        if (isMovingUp)    moveY -= 1.0f;
        if (isMovingDown)  moveY += 1.0f;
        if (isMovingLeft)  moveX -= 1.0f;
        if (isMovingRight) moveX += 1.0f;

        if (isKlaxoning) pPlayer->Klaxon();
        if (isFlashing) pPlayer->Flashing();
        if (isRocketLauncher) pPlayer->Rocket();
        if (isClear) ClearEntity(2);
        if (isDebug) debug = !debug;

        if (moveX != 0.0f || moveY != 0.0f) {
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
        boss = CreateEntity<Boss>(90, sf::Color::White, EntityType::Enemy, 3);
        pEnemies.push_back(boss);
        float x = 800;
        float y = 400;
        boss->SetPosition(x, y);
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
                newEnemy = CreateEntity<GoFast>(60, sf::Color::Yellow, EntityType::Enemy, 3);
                goFastCount++;
            } 
            break;
        case 1:
            if (pompierCount < maxPompier) {
                newEnemy = CreateEntity<Pompier>(30, sf::Color::Red, EntityType::Enemy, 3);
                pompierCount++;
            }
            break;
        case 2:
            if (camionCount < maxCamion) {
                newEnemy = CreateEntity<Camion>(40, sf::Color::Blue, EntityType::Enemy, 3);
                camionCount++;
            }
            break;
        case 3:
            if (btpCount < maxBTP) {
                newEnemy = CreateEntity<BTP>(30, sf::Color::Green, EntityType::Enemy, 3);
                btpCount++;
            }
            break;
        }

        if (newEnemy) {
            newEnemy->SetPosition(x, y);
            pEnemies.push_back(newEnemy);
        }
    }
}


void GameScene::OnUpdate()
{

    if (debug) {
        if (!pPlayer->ToDestroy()) {
            RectangleCollider* Testp = (RectangleCollider*)pPlayer->GetCollider();
            Debug::DrawRectangle(Testp->mParentEntity->GetPosition(0, 0).x, Testp->mParentEntity->GetPosition(0, 0).y, Testp->mWidth, Testp->mHeight, sf::Color::White);
        }

        for (auto& projectile : pProjectile) {
            if (!projectile->ToDestroy()) {
                if (projectile->GetCollider()->mType == Collider::ColliderType::Circle) {
                    CircleCollider* projCollider = (CircleCollider*)projectile->GetCollider();
                    Debug::DrawCircle(projCollider->mParentEntity->GetPosition(0.5f, 0.5f).x, projCollider->mParentEntity->GetPosition(0.5f, 0.5f).y, projCollider->GetRadius(), sf::Color::Cyan);
                }
                else if (projectile->GetCollider()->mType == Collider::ColliderType::AABB) {
                    RectangleCollider* projCollider = (RectangleCollider*)projectile->GetCollider();
                    Debug::DrawRectangle(projCollider->mParentEntity->GetPosition(0, 0).x, projCollider->mParentEntity->GetPosition(0, 0).y, projCollider->mWidth, projCollider->mHeight, sf::Color::Cyan);
                }
            }

        }
        for (auto& e : pEnemies) {
            if (!e->ToDestroy()) {
                RectangleCollider* eCollider = (RectangleCollider*)e->GetCollider();
                Debug::DrawRectangle(eCollider->mParentEntity->GetPosition(0, 0).x, eCollider->mParentEntity->GetPosition(0, 0).y,eCollider->mWidth,eCollider->mHeight, sf::Color::Red);
            }

        }
    }

    Debug::DrawText(50, 50, "Vague: " + std::to_string(wave), sf::Color::White);

    if (pPlayer->GetIsDead() && !win) {
        running = false;
        RemoveProjectile(EntityType::AllyProjectile);
        RemoveProjectile(EntityType::EnemyProjectile);
        ClearEntity(2);
        ClearEntity(1);
        Debug::DrawText(GetWindowWidth() / 2, GetWindowHeight() / 2, "PERDU", sf::Color::White);
    }
    else if (!running) {
        RemoveProjectile(EntityType::AllyProjectile);
        RemoveProjectile(EntityType::EnemyProjectile);
        ClearEntity(2);
        ClearEntity(1);
        win = true;
        Debug::DrawText(GetWindowWidth() / 2, GetWindowHeight() / 2, "VICTOIRE", sf::Color::White);
    }

    // Afficher la position de la souris
    sf::Vector2i mousePos = sf::Mouse::getPosition(*GetRenderWindow());
    Debug::DrawCircle(mousePos.x, mousePos.y, 7, sf::Color::White);

    // Nettoyage des ennemis d�truits
    pEnemies.erase(std::remove_if(pEnemies.begin(), pEnemies.end(),
        [](Entity* enemy) { return enemy->ToDestroy(); }), pEnemies.end());

    // G�rer la vague suivante
    if (pEnemies.empty() && running) {
        RemoveProjectile(EntityType::EnemyProjectile);
        wave++;
        pPlayer->SetFlashed(false);
        pPlayer->AddScore(100);
        LoadWave("../../../res/level.txt");
        if (pEnemies.empty()) {
            running = false;
        }
    }

    // Nettoyage des projectiles d�truits
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


void GameScene::AddProjectile(int size, float x, float y, sf::Color color, float dx, float dy, EntityType type, float angle, float speed) {
    Entity* p = nullptr;
    p = CreateEntity<Projectile>(size, color, type, 3);
    p->SetPosition(x, y);
    p->GoToDirection(dx, dy, speed);
    p->RotateDirection(angle);
    pProjectile.push_back(p);
}

void GameScene::AddProjectile(int Width, int Height, float x, float y, std::string path, float dx, float dy, EntityType type, float angle, float speed)
{
    Entity* p = nullptr;
    p = CreateEntity<Projectile>(path, Width, Height, type, 3);
    p->SetPosition(x, y);
    p->GoToDirection(dx, dy, speed);
    p->RotateDirection(angle);
    pProjectile.push_back(p);
}

void GameScene::AddProjectile(int Width, int Height, float x, float y, std::string path, int nbImage, float duration, float dx, float dy, EntityType type, float angle, float speed)
{
    Entity* p = nullptr;
    p = CreateEntity<Projectile>(path, Width, Height, nbImage, duration, type, 3);
    p->SetPosition(x, y);
    p->GoToDirection(dx, dy, speed);
    p->RotateDirection(angle);
    pProjectile.push_back(p);
}

void GameScene::AddGuidedProjectile(int size, float x, float y, sf::Color color, float speed, EntityType type, Entity* target, float Vx0, float Vy0) {
    if (Vx0 == -1) Vx0 = x;
    //size *= 20;
    GuidedProjectile* p = nullptr;
    //p = CreateEntity<GuidedProjectile>("../../../res/TestAnim/projectile3.png", size, size, 4, 0.2, type, 3);
    p = CreateEntity<GuidedProjectile>(size, color, type, 3);
    p->SetTarget(target);
    p->SetPosition(x, y);
    p->GoToDirection(Vx0, Vy0, speed);
    pProjectile.push_back(p);
}

void GameScene::AddGuidedProjectile(int Width, int Height, float x, float y, std::string path, float speed, EntityType type, Entity* target, float Vx0, float Vy0)
{
    if (Vx0 == -1) Vx0 = x;
    GuidedProjectile* p = nullptr;
    p = CreateEntity<GuidedProjectile>(path, Width, Height, type, 3);
    p->SetTarget(target);
    p->SetPosition(x, y);
    p->GoToDirection(Vx0, Vy0, speed);
    pProjectile.push_back(p);
}

void GameScene::AddGuidedProjectile(int Width, int Height, float x, float y, std::string path, int nbImage, float duration, float speed, EntityType type, Entity* target, float Vx0, float Vy0)
{
    if (Vx0 == -1) Vx0 = x;
    GuidedProjectile* p = nullptr;
    p = CreateEntity<GuidedProjectile>(path, Width, Height, nbImage, duration, type, 3);
    p->SetTarget(target);
    p->SetPosition(x, y);
    p->GoToDirection(Vx0, Vy0, speed);
    pProjectile.push_back(p);
}

void GameScene::RemoveProjectile(EntityType type) {

    for (Entity* projectile : pProjectile) {
        if (projectile->GetType() == type) {
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
        pPlayer->Destroy();
    }

}