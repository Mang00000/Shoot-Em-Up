#ifndef COLLIDERMANAGER_H__
#define COLLIDERMANAGER_H__

#include "Collider.h"
#include <functional>
#include <iostream>


class ColliderManager {
protected:
	static bool CircleCircle(Collider* Circle1, Collider* Circle2);
	static bool RectangleRectangle(Collider* Rectangle1, Collider* Rectangle2);
	static bool CircleRectangle(Collider* Circle, Collider* Rectangle);
	static bool RectangleCircle(Collider* Circle, Collider* Rectangle);

	static bool OOBBOOBB(Collider* OOBB1, Collider* OOBB2);

	inline static int AllowCollision[5][5] =
	{
		//Player  Enemy	 AllyProjectile	  EnemyProjectile Debug
		{0,		    1,		    0,		        1,			0}, // Player
		{1,			0,			1,				0,			0}, // Enemy
		{0,			1,			0,				1,			0}, //AllyProjectile
		{1,			0,			0,				0,			0}, //EnemyProjectile
		{0,			0,			0,				0,			0}, //Debug
	};

	inline static std::function<bool(Collider*,Collider*)> CollisionTab[3][3] =
	{
		{ColliderManager::CircleCircle, ColliderManager::CircleRectangle , ColliderManager::OOBBOOBB},
		{ColliderManager::RectangleCircle, ColliderManager::RectangleRectangle, ColliderManager::OOBBOOBB},
		{ColliderManager::OOBBOOBB, ColliderManager::OOBBOOBB, ColliderManager::OOBBOOBB},
	};

public:
	static bool ResolveCollision(Collider* pCollider1, Collider* pCollider2);
	static std::string PrintName(Collider::ColliderType type);

};


#endif // !COLLIDERMANAGER_H__
