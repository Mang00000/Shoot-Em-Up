#pragma once
#include "Entity.h"

class Projectile : public Entity
{
public:
	void OnCollision(Entity* other) override;

	void OnUpdate() override;
};

class ProjectileCamion : public Projectile
{
public:
	ProjectileCamion();
	void OnCollision(Entity* other) override;

	void OnUpdate() override;
};