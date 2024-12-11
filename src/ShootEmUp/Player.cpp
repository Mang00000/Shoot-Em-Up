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

    }
}

void Player::Flashing() {
    if (!isFlashing && flashCooldown >= flashTime) {
        isFlashing = true;
        flashCooldown = 0.0f;
        for (int i = -180; i < 180; i += 5) {
            GetScene<GameScene>()->AddProjectile(projectilesize, GetPosition().x, GetPosition().y, sf::Color::Yellow, 0, 0, i, projectilespeed, 1);
        }
    }
}
void Player::Klaxon() {
    if (!isInvicible && klaxonCooldown >= klaxonTime) {
        isInvicible = true;
        invicibleCooldown = 0.0f;
        klaxonCooldown = 0.0f;
    }
}
void Player::Rocket() {
    if (rocketCooldown < rocketTime) return;
    GetScene<GameScene>()->AddGuidedProjectile(7, GetPosition().x, GetPosition().y, sf::Color::White, 180, 1, GetScene<GameScene>()->GetClosestEnemy(this),-1000,500);
    GetScene<GameScene>()->AddGuidedProjectile(7, GetPosition().x, GetPosition().y, sf::Color::White, 180, 1, GetScene<GameScene>()->GetClosestEnemy(this), 0, -1000);
    GetScene<GameScene>()->AddGuidedProjectile(7, GetPosition().x, GetPosition().y, sf::Color::White, 180, 1, GetScene<GameScene>()->GetClosestEnemy(this), 0, 1000);
    GetScene<GameScene>()->AddGuidedProjectile(7, GetPosition().x, GetPosition().y, sf::Color::White, 180, 1, GetScene<GameScene>()->GetClosestEnemy(this), -1000, -500);
    rocketCooldown = 0;
}
void Player::OnUpdate()
{

    Debug::DrawText(50, 70, "Vie: " + std::to_string(hp), sf::Color::White);

    float x = GetPosition().x;
    float y = GetPosition().y;
    float r = GetWidth();
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

    Debug::DrawFilledRectangle(x + 34 + 5+7, y - 30, 6, 25, sf::Color::White);
    float BarHeight = (rocketCooldown / rocketTime) * 25;
    Debug::DrawFilledRectangle(x + 34 + 5+7, y - 30 + (25 - BarHeight), 6, BarHeight, sf::Color::Blue);

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
    else {
        if (AutoMode = true) Flashing();
    }
    if (rocketCooldown < rocketTime) {
        rocketCooldown += GetDeltaTime();
    }
    else {
        if (AutoMode = true) Rocket();
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
            if (GetScene<GameScene>()->GetWave() >= 5) {
                GetScene<GameScene>()->AddProjectile(projectilesize, x, y, sf::Color::Magenta, mousePos.x, mousePos.y, -8,projectilespeed, 1);
                GetScene<GameScene>()->AddProjectile(projectilesize, x, y, sf::Color::Magenta, mousePos.x, mousePos.y, 8, projectilespeed, 1);
            }
            if (GetScene<GameScene>()->GetWave() >= 10) {
                GetScene<GameScene>()->AddProjectile(projectilesize, x, y, sf::Color::Magenta, mousePos.x, mousePos.y, -16, projectilespeed, 1);
                GetScene<GameScene>()->AddProjectile(projectilesize, x, y, sf::Color::Magenta, mousePos.x, mousePos.y, 16, projectilespeed, 1);
            }
            if (GetScene<GameScene>()->GetWave() == 15 && !buffSpeed) {
                buffSpeed = true;
                projectilespeed *= 2;
                shotspeed /= 2;

            }
            if (GetScene<GameScene>()->GetWave() == 20 && !buffSize) {
                buffSize = true;
                projectilesize *= 2;
            }

            GetScene<GameScene>()->AddProjectile(projectilesize, x, y, sf::Color::Magenta, mousePos.x, mousePos.y, 0, projectilespeed, 1);

            cooldown = 0;
        }
    }
}