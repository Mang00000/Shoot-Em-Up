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

	static bool OOBBOOBB(Collider* OOBB1, Collider* OOBB2);

	inline static int AllowCollision[4][4] =
	{
		//Player  Enemy	 AllyProjectile	  EnemyProjectile
		{0,		    1,		    0,		        1}, // Player
		{1,			0,			1,				0}, // Enemy
		{0,			1,			0,				0}, //AllyProjectile
		{1,			0,			1,				0}, //EnemyProjectile
	};

	inline static std::function<bool(Collider*,Collider*)> CollisionTab[3][3] =
	{
		{ColliderManager::CircleCircle, ColliderManager::CircleRectangle , ColliderManager::OOBBOOBB},
		{ColliderManager::RectangleCircle, ColliderManager::RectangleRectangle, ColliderManager::OOBBOOBB},
		{ColliderManager::OOBBOOBB, ColliderManager::OOBBOOBB, ColliderManager::OOBBOOBB},
	};

public:
	static bool ResolveCollision(Collider* pCollider1, Collider* pCollider2);

};


#endif // !COLLIDERMANAGER_H__
