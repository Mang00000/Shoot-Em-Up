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

RectangleCollider::RectangleCollider(Entity* pParent, float width, float height) : Collider(pParent)
{
	mWidth = width;
	mHeight = height;
	mType = ColliderType::AABB;
}

