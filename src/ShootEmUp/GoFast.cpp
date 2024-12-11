#include "GoFast.h"
#include "Projectile.h"
#include "GameScene.h"
#include <iostream>
#include "Player.h"
#include<iostream>
#include "Debug.h"

void GoFast::OnCollision(Entity* other)
{
}


void GoFast::OnUpdate()
{
	if (start) {
		SetPosition(0 - GetRadius() * 2, GetPosition().y);
		start = false;

	}
	else if (rushmoment > time) {
		time += GetDeltaTime();
	} 
	else if (rushing) {
		GoToDirection(GetScene()->GetWindowWidth()+GetRadius(), GetPosition().y, 1000.0f);
		if (GetPosition().x > GetScene()->GetWindowWidth() + GetRadius()-2) {
			mToDestroy = true;
		}

	}
	else {
		rushing = true;
	}


	if (!flashlightOn && flashlightTimer > flashlightCd) {
		flashlightTimer = 0;
		flashlightOn = true;

		Debug::DrawCircle(GetPosition().x + GetRadius() * 2, GetPosition().y, 50, sf::Color::White);
		Debug::DrawCircle(GetPosition().x + GetRadius() * 2.5, GetPosition().y, 45, sf::Color::White);
		Debug::DrawCircle(GetPosition().x + GetRadius() * 3, GetPosition().y, 40, sf::Color::White);

	}
	else if (flashlightOn && flashlightTimer > flashlightCd) {
		flashlightOn = false;
	}
	else {

		flashlightTimer += GetDeltaTime();
	}

}