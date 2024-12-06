#ifndef COLLIDER_H__
#define COLLIDER_H__

#include "Entity.h"

class Collider {
protected:
	enum class ColliderType {
		CircleCollider,
	};
	Entity* mParentEntity;
	ColliderType mType;
public:
	Collider(Entity* mParent);
	virtual bool IsColliding(Collider* pOther) = 0;
	virtual bool IsInside(Collider* pOther) = 0;
};


class CircleCollider : public Collider {
private:
	int mRadius;
public:
	CircleCollider(int radius);
	bool IsColliding(Collider* pOther) override;
	bool IsInside(Collider* pOther) override;
};

#endif // !COLLIDER_H__
