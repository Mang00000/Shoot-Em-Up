#include "Projectile.h"

#include "Scene.h"
#include <iostream>

void Projectile::OnCollision(Entity* other)
{
}


void Projectile::OnUpdate()
{
	float x = GetPosition().x;
	float y = GetPosition().y;
	float r = GetRadius();
	float h = GetScene()->GetWindowHeight();
	float w = GetScene()->GetWindowWidth();

	if (x - r < 0 || y - r < 0 || x + r > w || y + r > h) mToDestroy = true;
}