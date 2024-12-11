#pragma once
#include "Entity.h"

class Projectile : public Entity
{
public:
	void OnCollision(Entity* other) override;

	void OnUpdate() override;
};

class GuidedProjectile : public Entity {
private:
	const float maxRotationSpeed = 0.3f;
public:
	void OnCollision(Entity* other) override;

	void OnUpdate() override;
};