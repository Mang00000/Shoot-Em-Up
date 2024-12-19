#pragma once

#include "Scene.h"
#include <vector>

class Player;
class Camion;
class GoFast;
class BTP;
class Pompier;
class Entity;
class Boss;
class Image;
class GameScene : public Scene
{
    Player* pPlayer;
    std::vector<Entity*> pEnemies; // Liste des ennemis
    std::vector<Entity*> pProjectile; // Liste des projectiles

private:

    static inline bool isPaused = false;
    int wave = 1;
    bool running = true;
    bool win = false;
    bool debug = false;

public:
    void OnInitialize() override;
    void OnEvent(const sf::Event& event) override;
    void OnUpdate() override;

    void GenerateEnemies(int count, int maxGoFast = 9999, int maxPompier = 9999, int maxCamion = 9999, int maxBTP = 9999);
    Player* GetPlayer();
    int GetWave() { return wave; }
    void AddGuidedProjectile(int size, float x, float y, sf::Color color, float speed, EntityType type, Entity* target, float Vx0 = -1, float Vy0 = 0);
    void RemoveProjectile(EntityType type);
    Entity* GetClosestEnemy(Entity* fromWho);
    sf::Vector2f GetEntityPosition(Entity* entity, float ratioX = 0.5f, float ratioY = 0.5f) const;
    void ClearEntity(int team);
    void LoadWave(const std::string& filename);
    bool IsWin() { return win; }
    void AddProjectile(int size, float x, float y, sf::Color color, float dx, float dy, EntityType type, float angle = 0, float speed = 0, int tag = 2);
};
