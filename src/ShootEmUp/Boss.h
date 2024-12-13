#pragma once
#include "Entity.h"

class Boss : public Entity
{
private:

public:
	void OnCollision(Entity* other) override;

	void OnUpdate() override;
};

