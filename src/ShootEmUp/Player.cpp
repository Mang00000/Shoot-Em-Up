#include "Player.h"

#include "Scene.h"
#include <iostream>

void Player::OnCollision(Entity* other)
{
}


void Player::OnUpdate()
{
	float x = GetPosition().x;
	float y = GetPosition().y;
	float r = GetRadius();
	float h = GetScene()->GetWindowHeight();
	float w = GetScene()->GetWindowWidth();

	if (x-r < 0) SetPosition(r, y);
	if (y-r < 0) SetPosition(x, r);
	if (x+r > w) SetPosition(w-r, y);
	if (y+r > h) SetPosition(x, h-r);

}