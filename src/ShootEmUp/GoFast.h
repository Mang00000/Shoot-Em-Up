#pragma once
#include "Entity.h"

class GoFast : public Entity
{
private:
	bool start = true;
	bool rushing = false;
	float rushmoment = 3.0f + rand() % 3;
	float time = 0.0f;

	bool flashlightOn = false;
	float flashlightCd = 0.005f;
	float flashlightTimer = 0.0f;
public:
	Player* pPlayer = GetScene<GameScene>()->GetPlayer();
	void OnCollision(Entity* other) override;

	void OnUpdate() override;
};

