#include "BTP.h"
#include "Projectile.h"
#include <iostream>
#include "Player.h"
#include "Utils.h" 

void BTP::OnCollision(Entity* other)
{
    if (other->IsTag(1)) {
        mToDestroy = true;
        other->Destroy();
    }
}

void BTP::OnUpdate()
{
    float M_PI = 3.14159;
    Player* pPlayer = pGM->GetPlayer();
    int x = pPlayer->GetPosition().x;
    int y = pPlayer->GetPosition().y;

    if (cooldown > shotspeed) {
        Projectile* p = GetScene()->CreateEntity<Projectile>(8, sf::Color::Red);
        p->SetPosition(GetPosition().x, GetPosition().y);
        p->GoToDirection(x, y, projectilespeed);
        p->SetTag(2);
        pList.push_back(p);  
        cooldown = 0; 
    }

    pList.erase(
        std::remove_if(pList.begin(), pList.end(), [](Projectile* p) {
            return p->ToDestroy(); 
            }),
        pList.end()
    );

    for (auto* p : pList) {
        sf::Vector2f currentPos = p->GetPosition(0.5f, 0.5f);
        sf::Vector2f targetPos = sf::Vector2f(x, y);

        sf::Vector2f directionToPlayer = targetPos - currentPos;
        Utils::Normalize(directionToPlayer); 

        float angleToPlayer = atan2(directionToPlayer.y, directionToPlayer.x);
        float currentAngle = atan2(p->GetDirection().y, p->GetDirection().x);

        float angleDifference = angleToPlayer - currentAngle;

        if (angleDifference > M_PI) {
            angleDifference -= 2 * M_PI;
        }
        else if (angleDifference < -M_PI) {
            angleDifference += 2 * M_PI;
        }

        if (angleDifference > maxRotationSpeed) {
            angleDifference = maxRotationSpeed;
        }
        else if (angleDifference < -maxRotationSpeed) {
            angleDifference = -maxRotationSpeed;
        }

        p->RotateDirection(angleDifference);
    }

    cooldown += GetDeltaTime();
}


