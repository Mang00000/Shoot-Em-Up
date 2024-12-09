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
    if (flashCooldown < flashTime) {
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

    Debug::DrawFilledRectangle(200, 50, 20, 100, sf::Color::White);
    float redBarHeight = (cooldown / shotspeed) * 100;
    Debug::DrawFilledRectangle(200, 50 + (100 - redBarHeight), 20, redBarHeight, sf::Color::Red);

    Debug::DrawFilledRectangle(225, 50, 20, 100, sf::Color::White);
    float yellowBarHeight = (flashCooldown / flashTime) * 100;
    Debug::DrawFilledRectangle(225, 50 + (100 - yellowBarHeight), 20, yellowBarHeight, sf::Color::Yellow);

    Debug::DrawFilledRectangle(250, 50, 20, 100, sf::Color::White);
    float greenBarHeight = (klaxonCooldown / klaxonTime) * 100;
    Debug::DrawFilledRectangle(250, 50 + (100 - greenBarHeight), 20, greenBarHeight, sf::Color::Green);

    float x = GetPosition().x;
    float y = GetPosition().y;
    float r = GetRadius();
    float h = GetScene()->GetWindowHeight();
    float w = GetScene()->GetWindowWidth();

    if (x - r < 0) SetPosition(r, y);
    if (y - r < 0) SetPosition(x, r);
    if (x + r > w) SetPosition(w - r, y);
    if (y + r > h) SetPosition(x, h - r);

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
