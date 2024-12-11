#include "Projectile.h"
#include "Scene.h"
#include <iostream>
#include <random>
#include "GameScene.h"
#include "Player.h"
#include "Utils.h"

void Projectile::OnCollision(Entity* other)
{
}


void Projectile::OnUpdate()
{
	float x = GetPosition().x;
	float y = GetPosition().y;
	float r = GetWidth();
	float h = GetScene()->GetWindowHeight();
	float w = GetScene()->GetWindowWidth();

	if (x - r < 0 || y - r < 0 || x + r > w || y + r > h) mToDestroy = true;
}

void GuidedProjectile::OnCollision(Entity* other)
{
}

void GuidedProjectile::OnUpdate()
{
    float M_PI = 3.14159;
	float x = GetPosition().x;
	float y = GetPosition().y;
	float r = GetWidth();
	float h = GetScene()->GetWindowHeight();
	float w = GetScene()->GetWindowWidth();

	if (x - r < 0 || y - r < 0 || x + r > w || y + r > h) mToDestroy = true;

    sf::Vector2f currentPos = GetPosition(0.5f, 0.5f);
    sf::Vector2f targetPos = sf::Vector2f(x, y);

    sf::Vector2f directionToPlayer = targetPos - currentPos;
    Utils::Normalize(directionToPlayer);

    float angleToPlayer = atan2(directionToPlayer.y, directionToPlayer.x);
    float currentAngle = atan2(GetDirection().y, GetDirection().x);

    float angleDifference = angleToPlayer - currentAngle;

    if (angleDifference > M_PI) {
        angleDifference -= 2 * M_PI;
    }
    else if (angleDifference < -M_PI) {
        angleDifference += 2 * M_PI;
    }

    if (angleDifference > maxRotationSpeed) {
        angleDifference = maxRotationSpeed;
    }
    else if (angleDifference < -maxRotationSpeed) {
        angleDifference = -maxRotationSpeed;
    }

    RotateDirection(angleDifference);
}