#ifndef COLLIDERMANAGER_H__
#define COLLIDERMANAGER_H__

class Collider;
#include <functional>
#include <iostream>


class ColliderManager {
protected:
	static bool CircleCircle(Collider* Circle1, Collider* Circle2);
	static bool RectangleRectangle(Collider* Rectangle1, Collider* Rectangle2);
	static bool CircleRectangle(Collider* Circle, Collider* Rectangle);
	static bool RectangleCircle(Collider* Circle, Collider* Rectangle);

	inline static std::function<bool(Collider*,Collider*)> CollisionTab[(int)Collider::ColliderType::Count][(int)Collider::ColliderType::Count] =
	{
		{ColliderManager::CircleCircle, ColliderManager::CircleRectangle},
		{ColliderManager::RectangleCircle, ColliderManager::RectangleRectangle}
	};

public:
	static bool ResolveCollision(Collider* pCollider1, Collider* pCollider2);

};


#endif // !COLLIDERMANAGER_H__
