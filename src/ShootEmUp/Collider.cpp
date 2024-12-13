#include "Collider.h"
#include "Utils.h"

Collider::Collider(Entity* Parent)
{
	mParentEntity = Parent;
}

CircleCollider::CircleCollider(Entity* mParent, int radius) : Collider(mParent)
{
	mRadius = radius;
	mType = ColliderType::Circle;
}

RectangleCollider::RectangleCollider(Entity* pParent, int width, int height) : Collider(pParent)
{
	mWidth = width;
	mHeight = height;
	mType = ColliderType::AABB;
}

OOBBCollider::OOBBCollider(Entity* pParent, int width, int height, sf::Vector2f center, float angle) : Collider(pParent)
{
	mWidth = width;
	mHeight = height;
	mAngle = angle;
	mType = ColliderType::OOBB;

	float AngleRad = angle * (std::numbers::pi / 180);

	sf::Vector2f Width2 = sf::Vector2f(cos(AngleRad) * width, sin(AngleRad) * width);
	sf::Vector2f Height2 = sf::Vector2f(-sin(AngleRad) * height, cos(AngleRad) * height);


	mTrueWidth = Width2;
	mTrueHeight = Height2;

	sf::Vector2f FirstPoint = sf::Vector2f(center.x - Width2.x / 2 - Height2.x / 2, center.y - Width2.y / 2 - Height2.y / 2);


	mPoints.push_back(FirstPoint);
	mPoints.push_back(FirstPoint + Width2);
	mPoints.push_back(FirstPoint + Width2 + Height2);
	mPoints.push_back(FirstPoint + Height2);

	mNormals.push_back(Utils::Normalize2(Height2));
	mNormals.push_back(Utils::Normalize2(-Height2));
	mNormals.push_back(Utils::Normalize2(Width2));
	mNormals.push_back(Utils::Normalize2(-Width2));

}
