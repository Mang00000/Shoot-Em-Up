#include "Player.h"

#include "Scene.h"
#include <iostream>
#include "Projectile.h"
#include "Debug.h"

void Player::OnCollision(Entity* other)
{
    if (other->IsTag(2) && !isInvicible) {
        hp--;
        other->Destroy();
        isInvicible = true;
    }
    if (hp <= 0) {
        mToDestroy = true;
    }
}

void Player::Flashing() {
    if (!isFlashing && flashCooldown >= flashTime) {
        isFlashing = true;
        flashCooldown = 0.0f;
        Projectile* p = GetScene()->CreateEntity<Projectile>(50, sf::Color::White);
        p->SetPosition(GetPosition().x, GetPosition().y);
        p->SetTag(1);
    }
}
void Player::Klaxon() {
    if (!isInvicible && klaxonCooldown >= klaxonTime) {
        isInvicible = true;
        invicibleCooldown = 0.0f;
        klaxonCooldown = 0.0f;
    }
}
void Player::OnUpdate()
{

    Debug::DrawText(50, 70, "Vie: " + std::to_string(hp), sf::Color::White);

    float x = GetPosition().x;
    float y = GetPosition().y;
    float r = GetRadius();
    float h = GetScene()->GetWindowHeight();
    float w = GetScene()->GetWindowWidth();

    if (x - r < 0) SetPosition(r, y);
    if (y - r < 0) SetPosition(x, r);
    if (x + r > w) SetPosition(w - r, y);
    if (y + r > h) SetPosition(x, h - r);

    Debug::DrawFilledRectangle(x+20+5, y-30, 6, 25, sf::Color::White);
    float redBarHeight = (cooldown / shotspeed) * 25;
    Debug::DrawFilledRectangle(x + 20+5, y - 30 + (25 - redBarHeight), 6, redBarHeight, sf::Color::Red);

    Debug::DrawFilledRectangle(x + 27+5, y - 30, 6, 25, sf::Color::White);
    float yellowBarHeight = (flashCooldown / flashTime) * 25;
    Debug::DrawFilledRectangle(x + 27+5, y - 30 + (25- yellowBarHeight), 6, yellowBarHeight, sf::Color::Yellow);

    Debug::DrawFilledRectangle(x + 34+5, y - 30, 6, 25, sf::Color::White);
    float greenBarHeight = (klaxonCooldown / klaxonTime) * 25;
    Debug::DrawFilledRectangle(x + 34+5, y - 30 + (25 - greenBarHeight), 6, greenBarHeight, sf::Color::Green);

    if (isFlashing) {
        if (flashingCooldown < flashingTime) {
            flashingCooldown += GetDeltaTime();
        }
        else {
            flashingCooldown = 0;
            isFlashing = false;
            
        }
    }

    if (isInvicible) {
        invicibleCooldown += GetDeltaTime();
        Debug::DrawCircle(x, y, 15, sf::Color::White);
        if (invicibleCooldown >= invicibleTime) {
            isInvicible = false;
            invicibleCooldown = 0.0f;
        }
    }

    if (flashCooldown < flashTime) {
        flashCooldown += GetDeltaTime();
    }
    if (klaxonCooldown < klaxonTime && !isInvicible) {
        klaxonCooldown += GetDeltaTime();
    }

    if (cooldown < shotspeed) {
        cooldown += GetDeltaTime();
    }
    else {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*GetScene()->GetRenderWindow());

        if (mousePos.x >= 0 && mousePos.y >= 0) {


            auto createProjectile = [&](float rotationOffset) {
                Projectile* p = GetScene()->CreateEntity<Projectile>(projectilesize, sf::Color::Magenta);
                p->SetPosition(x,y);
                p->GoToDirection(mousePos.x, mousePos.y, projectilespeed);
                p->SetTag(1);
                p->RotateDirection(rotationOffset);
                };

            if (pGM->GetWave() >= 5) {
                createProjectile(-8);
                createProjectile(8);
            }
            if (pGM->GetWave() >= 10) {
                createProjectile(-16);
                createProjectile(16);
            }
            if (pGM->GetWave() == 15 && !buffSpeed) {
                buffSpeed = true;
                projectilespeed *= 2;
                shotspeed /= 2;

            }
            if (pGM->GetWave() == 20 && !buffSize) {
                buffSize = true;
                projectilesize *= 2;
            }

            createProjectile(0);

            cooldown = 0;
        }
    }
}
