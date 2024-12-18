#include "ColliderManager.h"
#include "Collider.h"
#include "Utils.h"

bool ColliderManager::CircleCircle(Collider* Circle1, Collider* Circle2)
{
    CircleCollider* C1 = (CircleCollider*)Circle1;
    sf::Vector2f Center1 = C1->mParentEntity->GetCenter();

    float C1CenterX = Center1.x;
    float C1CenterY = Center1.y;
    float C1Radius = C1->mRadius;

    CircleCollider* C2 = (CircleCollider*)Circle2;
    sf::Vector2f Center2 = C2->mParentEntity->GetCenter();

    float C2CenterX = Center2.x;
    float C2CenterY = Center2.y;
    float C2Radius = C2->mRadius;


    return Utils::GetDistance(C1CenterX, C1CenterY, C2CenterX, C2CenterY) < C1Radius + C2Radius;
}

bool ColliderManager::RectangleRectangle(Collider* Rectangle1, Collider* Rectangle2)
{
    RectangleCollider* R1 = (RectangleCollider*)Rectangle1;
    sf::Vector2f TopLeft1 = R1->mParentEntity->GetTopLeft();

    float R1X = TopLeft1.x;
    float R1Y = TopLeft1.y;
    float R1Width = R1->mWidth;
    float R1Height = R1->mHeight;

    RectangleCollider* R2 = (RectangleCollider*)Rectangle2;
    sf::Vector2f TopLeft2 = R2->mParentEntity->GetTopLeft();
    float R2X = TopLeft2.x;
    float R2Y = TopLeft2.y;
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
    sf::Vector2f Center1 = Circle1->mParentEntity->GetCenter();

    float C1CenterX = Center1.x;
    float C1CenterY = Center1.y;
    int C1Radius = Circle1->mRadius;

    RectangleCollider* Rectangle1 = (RectangleCollider*)Rectangle;
    sf::Vector2f TopLeft1 = Rectangle1->mParentEntity->GetTopLeft();

    float R1X = TopLeft1.x;
    float R1Y = TopLeft1.y;
    float R1Width = Rectangle1->mWidth;
    float R1Height = Rectangle1->mHeight;


    float TestX = C1CenterX;
    float TestY = C1CenterY;

    if (C1CenterX < R1X) TestX = R1X;
    else if (C1CenterX > R1X + R1Width) TestX = R1X + R1Width;
    if (C1CenterY < R1Y) TestY = R1Y;
    else if (C1CenterY > R1Y + R1Height) TestY = R1Y + R1Height;

    return Utils::GetDistance(TestX, TestY, C1CenterX, C1CenterY) <= C1Radius;
}

bool ColliderManager::RectangleCircle(Collider* Circle, Collider* Rectangle)
{
    return CircleRectangle(Rectangle, Circle);
}

bool ColliderManager::OOBBOOBB(Collider* OOBB1, Collider* OOBB2)
{
    OOBBCollider* O1 = (OOBBCollider*)OOBB1;
    OOBBCollider* O2 = (OOBBCollider*)OOBB2;

    for (int i = 0; i < O1->mNormals.size(); i++) {
        float O1Min;
        float O1Max;
        float O2Min;
        float O2Max;
        Utils::SATTest(O1->mNormals[i], O1->mPoints, O1Min, O1Max);
        Utils::SATTest(O1->mNormals[i], O2->mPoints, O2Min, O2Max);
        if (!Utils::Overlaps(O1Min, O1Max, O2Min, O2Max)) {
            return false;
        }
    }

    for (int i = 0; i < O2->mNormals.size(); i++) {
        float O1Min;
        float O1Max;
        float O2Min;
        float O2Max;
        Utils::SATTest(O2->mNormals[i], O1->mPoints, O1Min, O1Max);
        Utils::SATTest(O2->mNormals[i], O2->mPoints, O2Min, O2Max);
        if (!Utils::Overlaps(O1Min, O1Max, O2Min, O2Max)) {
            return false;
        }
    }

    return true;
}

bool ColliderManager::ResolveCollision(Collider* pCollider1, Collider* pCollider2)
{
    if (AllowCollision[(int)pCollider1->mParentEntity->GetType()][(int)pCollider2->mParentEntity->GetType()] == 0) {
        return false;
    }

    return CollisionTab[(int)pCollider1->mType][(int)pCollider2->mType](pCollider1, pCollider2);
}
