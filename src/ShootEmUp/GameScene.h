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

    std::vector<Entity*> enemies; // Liste des ennemis
    int wave = 1;

public:
    void OnInitialize() override;
    void OnEvent(const sf::Event& event) override;
    void OnUpdate() override;

    void GenerateEnemies(int count, int maxGoFast = 9999, int maxPompier = 9999, int maxCamion = 9999, int maxBTP = 9999);
    Player* GetPlayer();
    int GetWave() { return wave; }
};
