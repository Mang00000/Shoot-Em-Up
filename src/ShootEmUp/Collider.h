#ifndef COLLIDER_H__
#define COLLIDER_H__

#include "Entity.h"

class Collider {
protected:
	enum class ColliderType {
		CircleCollider,
		RectangleCollider
	};
	Entity* mParentEntity;
	ColliderType mType;
public:
	Collider(Entity* Parent);
	virtual bool IsColliding(Collider* pOther) = 0;
	virtual bool IsInside(Collider* pOther) = 0;
	ColliderType GetType() { return mType; }
	Entity* GetEntity() { return mParentEntity; }
};


class CircleCollider : public Collider {
private:
	int mRadius;
public:
	CircleCollider(Entity* pParent, int radius);
	bool IsColliding(Collider* pOther) override;
	bool IsInside(Collider* pOther) override;
};

class RectangleCollider : public Collider {
private:
	sf::Vector2f mTopLeft;
	float mWidth;
	float mHeight;
public:
	RectangleCollider(Entity* pParent, float Width, float Height);
	bool IsColliding(Collider* pother) override;
	bool IsInside(Collider* pOther) override;
};

#endif // !COLLIDER_H__
