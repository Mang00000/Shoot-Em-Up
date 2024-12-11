#ifndef COLLIDER_H__
#define COLLIDER_H__

#include "Entity.h"

struct Collider {
	enum class ColliderType {
		Circle,
		AABB,

		Count
	};
	Entity* mParentEntity;
	ColliderType mType;
	Collider(Entity* Parent);
};


struct CircleCollider : public Collider {
	int mRadius;
	CircleCollider(Entity* pParent, int radius);
};

struct RectangleCollider : public Collider {
	int mWidth;
	int mHeight;

	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }
	RectangleCollider(Entity* pParent, float Width, float Height);
};

#endif // !COLLIDER_H__
