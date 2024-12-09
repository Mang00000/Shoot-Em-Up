#include "Collider.h"
#include "Utils.h"

Collider::Collider(Entity* Parent)
{
	mParentEntity = Parent;
}

CircleCollider::CircleCollider(Entity* mParent, int radius) : Collider(mParent)
{
	mRadius = radius;
	mType = ColliderType::CircleCollider;
}

bool CircleCollider::IsColliding(Collider* pOther)
{
	Entity* CurrentEntity = this->GetEntity();
	float CurrentX = CurrentEntity->GetPosition().x;
	float CurrentY = CurrentEntity->GetPosition().y;

	Entity* OtherEntity = pOther->GetEntity();
	float OtherX = OtherEntity->GetPosition().x;
	float OtherY = OtherEntity->GetPosition().y;

	if (pOther->GetType() == ColliderType::CircleCollider) {
		return Utils::GetDistance(CurrentX, CurrentY, OtherX, OtherY) < this->mRadius + dynamic_cast<CircleCollider*>(pOther)->mRadius;
	}
	return false;
}

bool CircleCollider::IsInside(Collider* pOther)
{
	Entity* CurrentEntity = this->GetEntity();
	float CurrentX = CurrentEntity->GetPosition().x;
	float CurrentY = CurrentEntity->GetPosition().y;

	Entity* OtherEntity = pOther->GetEntity();
	float OtherX = OtherEntity->GetPosition().x;
	float OtherY = OtherEntity->GetPosition().y;

	if (pOther->GetType() == ColliderType::CircleCollider) {
		float Distance = Utils::GetDistance(CurrentX, CurrentY, OtherX, OtherY);
		return dynamic_cast<CircleCollider*>(pOther)->mRadius > this->mRadius + Distance;
	}
	return false;
}

RectangleCollider::RectangleCollider(Entity* pParent, float Width, float Height) : Collider(pParent)
{
	mWidth = Width;
	mHeight = Height;
	mTopLeft = pParent->GetPosition(0, 0);
	mType = ColliderType::RectangleCollider;
}

bool RectangleCollider::IsColliding(Collider* pOther)
{
	if (pOther->GetType() == ColliderType::RectangleCollider) {
		Entity* CurrentEntity = this->GetEntity();
		float CurrentX = mTopLeft.x;
		float CurrentY = mTopLeft.x;
		float CurrentW = mWidth;
		float CurrentH = mHeight;

		RectangleCollider* OtherRect = dynamic_cast<RectangleCollider*>(pOther);
		float OtherX = OtherRect->mTopLeft.x;
		float OtherY = OtherRect->mTopLeft.y;
		float OtherW = OtherRect->mWidth;
		float OtherH = OtherRect->mHeight;

		return CurrentX + CurrentW >= OtherX &&
			CurrentX <= OtherX + OtherW &&
			CurrentY + CurrentH >= OtherY &&
			CurrentY <= OtherY + OtherH;
	}
	else if (pOther->GetType() == ColliderType::CircleCollider) {
		Entity* OtherEntity = pOther->GetEntity();
		float OtherX = OtherEntity->GetPosition().x;
		float OtherY = OtherEntity->GetPosition().y;

	}
	

	return false;
}
