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

OOBBCollider::OOBBCollider(Entity* pParent, int width, int height, sf::Vector2f startpos, float angle) : Collider(pParent)
{
	mWidth = width;
	mHeight = height;
	mAngle = angle;

	sf::Vector2f Width2 = sf::Vector2f(cos(angle) * width, sin(angle) * width);
	sf::Vector2f Height2 = sf::Vector2f(-sin(angle) * height, cos(angle) * height);

	mPoints[0] = startpos;
	mPoints[1] = startpos + Width2;
	mPoints[2] = startpos + Width2 + Height2;
	mPoints[3] = startpos + Height2;

	mNormals[0] = Utils::Normalize2(Height2);
	mNormals[1] = Utils::Normalize2(Width2);

}
