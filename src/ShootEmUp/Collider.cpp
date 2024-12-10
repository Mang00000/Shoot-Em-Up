#include "Collider.h"
#include "Utils.h"

Collider::Collider(Entity* Parent)
{
	mParentEntity = Parent;
}

CircleCollider::CircleCollider(Entity* mParent, int radius, float ratioX, float ratioY) : Collider(mParent)
{
	mCenter = mParent->GetPosition(ratioX,ratioY);
	mRadius = radius;
	mType = ColliderType::Circle;
}

RectangleCollider::RectangleCollider(Entity* pParent, float Width, float Height, float ratioX, float ratioY) : Collider(pParent)
{
	mWidth = Width;
	mHeight = Height;
	mTopLeft = pParent->GetPosition(ratioX, ratioY);


	mType = ColliderType::AABB;
}

