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
	sf::Vector2f mCenter;
	CircleCollider(Entity* pParent, int radius, float ratioX = 0.5f, float RatioY = 0.5f);
};

struct RectangleCollider : public Collider {
	sf::Vector2f mTopLeft;
	float mWidth;
	float mHeight;
	RectangleCollider(Entity* pParent, float Width, float Height, float ratioX = 0.0f, float ratioY = 0.0f);
};

#endif // !COLLIDER_H__
