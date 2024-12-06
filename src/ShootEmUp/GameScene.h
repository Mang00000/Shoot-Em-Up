#pragma once

#include "Scene.h"

class Player;
class Camion;
class GoFast;
class BTP;
class Pompier;


class GameScene : public Scene
{

	Player* pEntity2;

	Camion* camion;
	Camion* camion2;

	GoFast* f;

	BTP* btp;
		
	Player* pEntitySelected;

	Pompier* pomp;

private:
	void TrySetSelectedEntity(Player* pEntity, int x, int y);

public:
	void OnInitialize() override;
	void OnEvent(const sf::Event& event) override;
	void OnUpdate() override;
	Player* GetPlayer();
};


