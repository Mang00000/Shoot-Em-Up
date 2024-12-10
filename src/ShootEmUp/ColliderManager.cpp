#include "ColliderManager.h"
#include "Collider.h"
#include "Utils.h"

bool ColliderManager::CircleCircle(Collider* Circle1, Collider* Circle2)
{
    CircleCollider* C1 = (CircleCollider*)Circle1;
    float C1CenterX = C1->mCenter.x;
    float C1CenterY = C1->mCenter.y;
    float C1Radius = C1->mRadius;

    CircleCollider* C2 = (CircleCollider*)Circle2;
    float C2CenterX = C2->mCenter.x;
    float C2CenterY = C2->mCenter.y;
    float C2Radius = C2->mRadius;


    return Utils::GetDistance(C1CenterX, C1CenterY, C2CenterX, C2CenterY) < C1Radius + C2Radius;
}

bool ColliderManager::RectangleRectangle(Collider* Rectangle1, Collider* Rectangle2)
{
    RectangleCollider* R1 = (RectangleCollider*)Rectangle1;
    float R1X = R1->mTopLeft.x;
    float R1Y = R1->mTopLeft.y;
    float R1Width = R1->mWidth;
    float R1Height = R1->mHeight;

    RectangleCollider* R2 = (RectangleCollider*)Rectangle2;
    float R2X = R2->mTopLeft.x;
    float R2Y = R2->mTopLeft.y;
    float R2Width = R2->mWidth;
    float R2Height = R2->mHeight;


    return R1X + R1Width >= R2X &&
        R1X <= R2X + R2Width &&
        R1Y + R1Height >= R2Y &&
        R1Y <= R2Y + R2Height;
}

bool ColliderManager::CircleRectangle(Collider* Circle, Collider* Rectangle)
{
    CircleCollider* Circle1 = (CircleCollider*)Circle;
    float C1CenterX = Circle1->mCenter.x;
    float C1CenterY = Circle1->mCenter.y;
    int C1Radius = Circle1->mRadius;

    RectangleCollider* Rectangle1 = (RectangleCollider*)Rectangle;
    float R1X = Rectangle1->mTopLeft.x;
    float R1Y = Rectangle1->mTopLeft.y;
    float R1Width = Rectangle1->mWidth;
    float R1Height = Rectangle1->mHeight;


    float TestX = C1CenterX;
    float TestY = C1CenterY;

    if (C1CenterX < R1X) TestX = R1X;
    else if (C1CenterX > R1X + R1Width) TestX = R1X + R1Width;
    if (C1CenterY < R1Y) TestY = R1Y;
    else if (C1CenterY > R1Y + R1Height) TestY = R1Y + R1Height;

    return Utils::GetDistance(C1CenterX, C1CenterY, R1X, R1Y) <= C1Radius;
}

bool ColliderManager::RectangleCircle(Collider* Circle, Collider* Rectangle)
{
    return CircleRectangle(Rectangle, Circle);
}

bool ColliderManager::ResolveCollision(Collider* pCollider1, Collider* pCollider2)
{
    return CollisionTab[(int)pCollider1->mType][(int)pCollider2->mType](pCollider1, pCollider2);
}
