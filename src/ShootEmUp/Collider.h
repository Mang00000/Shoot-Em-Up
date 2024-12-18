#ifndef COLLIDER_H__
#define COLLIDER_H__

#include "Entity.h"
#include <vector>

struct Collider {
	enum class ColliderType {
		Circle,
		AABB,
		OOBB,

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
	RectangleCollider(Entity* pParent, int Width, int Height);
};

struct OOBBCollider : public Collider {
	std::vector<sf::Vector2f> mPoints;
	std::vector<sf::Vector2f> mNormals;

	int mWidth;
	int mHeight;
	float mAngle;

	sf::Vector2f mTrueWidth;
	sf::Vector2f mTrueHeight;

	int GetWidth() { return mWidth; }
	int GetHeight() { return mHeight; }
	
	OOBBCollider(Entity* pParent, int width, int height, sf::Vector2f center, float angle);

};

#endif // !COLLIDER_H__
