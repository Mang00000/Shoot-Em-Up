#pragma once

#include "Scene.h"

class Player;
class Camion;
class GoFast;
class BTP;
class Pompier;

#include <vector>

class GameScene : public Scene
{
    Player* pPlayer;
    std::vector<Entity*> pEnemies; // Liste des ennemis
    std::vector<Entity*> pProjectile; // Liste des projectiles
    int wave = 1;
    bool running = true;

public:
    void OnInitialize() override;
    void OnEvent(const sf::Event& event) override;
    void OnUpdate() override;

    void GenerateEnemies(int count, int maxGoFast = 9999, int maxPompier = 9999, int maxCamion = 9999, int maxBTP = 9999);
    Player* GetPlayer();
    int GetWave() { return wave; }
    void AddProjectile(int size, float x, float y, sf::Color color, float dx, float dy, float angle = 0, float speed = 0, std::string tag = "EnemyProj");
    void AddGuidedProjectile(int size, float x, float y, sf::Color color, float speed, std::string tag, Entity* target, float Vx0 = -1, float Vy0 = 0);
    void RemoveProjectile(std::string tag);
    Entity* GetClosestEnemy(Entity* fromWho);
    sf::Vector2f GetEntityPosition(Entity* entity, float ratioX = 0.5f, float ratioY = 0.5f) const;
    void ClearEntity(int team);
    void LoadWave(const std::string& filename);
};
