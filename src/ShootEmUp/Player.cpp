#include "Player.h"
#include "Scene.h"
#include "Projectile.h"
#include "Debug.h"
#include <iostream>

Player::Player() {
    // Reset les abilites au Init
    flashCooldown.Reset();
    rocketCooldown.Reset();
    klaxonCooldown.Reset();
}
void Player::OnCollision(Entity* other) {
    if ((other->IsTag("EnemyProj") || other->IsTag("Enemy")) && !invincibleCooldown.isActive) { // Si projectile ennemi
        stats.hp--;
        if (other->IsTag("EnemyProj")) {
            other->Destroy();
        }
        invincibleCooldown.Reset();
    }
    if (stats.hp <= 0) {
        isDead = true;
    }
}


// Draws the cooldown bars
void Player::DrawCooldownBars() {
    sf::Vector2f position = GetPosition();
    float x = position.x + 20;
    float y = position.y - 30;
    const float barHeight = 30.0f;
    const float barWidth = 6.0f;
    const float spacing = 7.0f;

    struct CooldownBar {
        const Cooldown& cooldown;
        sf::Color color;
        float offsetX;
    };

    CooldownBar bars[] = {
        {shotCooldown, sf::Color::Red, 0},
        {flashCooldown, sf::Color::Yellow, spacing},
        {klaxonCooldown, sf::Color::Green, 2 * spacing},
        {rocketCooldown, sf::Color::Blue, 3 * spacing}
    };

    for (const auto& bar : bars) {
        Debug::DrawFilledRectangle(x + bar.offsetX, y, barWidth, barHeight, sf::Color::White);
        float filledHeight = (bar.cooldown.currentTime / bar.cooldown.maxTime) * barHeight;
        Debug::DrawFilledRectangle(x + bar.offsetX, y + (barHeight - filledHeight), barWidth, filledHeight, bar.color);

void Player::Flashing() {
    if (!isFlashing && flashCooldown >= flashTime) {
        isFlashing = true;
        flashCooldown = 0.0f;
        Projectile* p = GetScene()->CreateEntity<Projectile>(50, sf::Color::White, EntityType::AllyProjectile);
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

void Player::Shoot() {
    sf::Vector2i mousePos = sf::Mouse::getPosition(*GetScene()->GetRenderWindow());
    if (mousePos.x >= 0 && mousePos.y >= 0 && shotCooldown.IsReady()) {
        auto* scene = GetScene<GameScene>();
        int wave = scene->GetWave();

        ApplyBuff(wave);

        scene->AddProjectile(stats.projectileSize, GetPosition().x, GetPosition().y, sf::Color::Magenta, mousePos.x, mousePos.y, 0, stats.projectileSpeed, "PlayerProj");

        if (wave >= 5) {
            scene->AddProjectile(stats.projectileSize, GetPosition().x, GetPosition().y, sf::Color::Magenta, mousePos.x, mousePos.y, -8, stats.projectileSpeed, "PlayerProj");
            scene->AddProjectile(stats.projectileSize, GetPosition().x, GetPosition().y, sf::Color::Magenta, mousePos.x, mousePos.y, 8, stats.projectileSpeed, "PlayerProj");
        }
        if (wave >= 10) {
            scene->AddProjectile(stats.projectileSize, GetPosition().x, GetPosition().y, sf::Color::Magenta, mousePos.x, mousePos.y, -16, stats.projectileSpeed, "PlayerProj");
            scene->AddProjectile(stats.projectileSize, GetPosition().x, GetPosition().y, sf::Color::Magenta, mousePos.x, mousePos.y, 16, stats.projectileSpeed, "PlayerProj");
        }

        shotCooldown.Reset();
    }
}

void Player::HandleCooldowns() {
    float deltaTime = GetDeltaTime();
    shotCooldown.Update(deltaTime);
    flashCooldown.Update(deltaTime);
    rocketCooldown.Update(deltaTime);
    klaxonCooldown.Update(deltaTime);
    invincibleCooldown.Update(deltaTime);
}

void Player::OnUpdate() {
    if (isDead || GetScene<GameScene>()->IsWin()) return;
    Debug::DrawText(50, 70, "Vie: " + std::to_string(stats.hp), sf::Color::White);
    Debug::DrawText(50, 90, "Score: " + std::to_string(score), sf::Color::White);
    sf::Vector2f position = GetPosition();
    float radius = GetWidth() / 2;
    float windowWidth = GetScene()->GetWindowWidth();
    float windowHeight = GetScene()->GetWindowHeight();

    // Show invincible debug
    if (invincibleCooldown.isActive) {
        Debug::DrawCircle(position.x, position.y, 15, sf::Color::Red);
    }

    // Window Collision
    if (position.x - radius < 0) SetPosition(radius, position.y);
    if (position.y - radius < 0) SetPosition(position.x, radius);
    if (position.x + radius > windowWidth) SetPosition(windowWidth - radius, position.y);
    if (position.y + radius > windowHeight) SetPosition(position.x, windowHeight - radius);

    if (isFlashed) return;
    // Auto Mode
    if (autoMode) {
        Flashing();
        Rocket();
    }
    // Handler
    HandleCooldowns();
    Shoot();
    DrawCooldownBars();
}

// Applies buffs based on wave
void Player::ApplyBuff(int wave) {
    if (wave == 3 && !buffSpeed) {
        buffSpeed = true;
        stats.projectileSpeed *= 2;
        stats.shotSpeed *= 2;
        shotCooldown.maxTime /= stats.shotSpeed;
    }
    if (wave == 20 && !buffSize) {
        buffSize = true;
        stats.projectileSize *= 2;
    }
}

// Abilities (Flashing, Klaxon, Rocket)
void Player::Flashing() {
    if (!flashCooldown.isActive && flashCooldown.IsReady()) {
        flashCooldown.Reset();
        for (int i = -180; i < 180; i += 5) {
            GetScene<GameScene>()->AddProjectile(stats.projectileSize, GetPosition().x, GetPosition().y, sf::Color::Yellow, 0, 0, i, stats.projectileSpeed, "PlayerProj");
    else {
        sf::Vector2i mousePos = sf::Mouse::getPosition(*GetScene()->GetRenderWindow());

        if (mousePos.x >= 0 && mousePos.y >= 0) {
            if (GetScene<GameScene>()->GetWave() >= 5) {
                GetScene<GameScene>()->AddProjectile(projectilesize, x, y, sf::Color::Magenta, mousePos.x, mousePos.y, EntityType::AllyProjectile, -8,projectilespeed, 1);
                GetScene<GameScene>()->AddProjectile(projectilesize, x, y, sf::Color::Magenta, mousePos.x, mousePos.y, EntityType::AllyProjectile, 8, projectilespeed, 1);
            }
            if (GetScene<GameScene>()->GetWave() >= 10) {
                GetScene<GameScene>()->AddProjectile(projectilesize, x, y, sf::Color::Magenta, mousePos.x, mousePos.y, EntityType::AllyProjectile, -16, projectilespeed, 1);
                GetScene<GameScene>()->AddProjectile(projectilesize, x, y, sf::Color::Magenta, mousePos.x, mousePos.y, EntityType::AllyProjectile, 16, projectilespeed, 1);
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

            GetScene<GameScene>()->AddProjectile(projectilesize, x, y, sf::Color::Magenta, mousePos.x, mousePos.y, EntityType::AllyProjectile, 0, projectilespeed, 1);

            cooldown = 0;
        }
    }
}

void Player::Klaxon() {
    if (!invincibleCooldown.isActive && klaxonCooldown.IsReady()) {
        invincibleCooldown.Reset();
        klaxonCooldown.Reset();
    }
}

void Player::Rocket() {
    if (rocketCooldown.IsReady()) {
        auto* scene = GetScene<GameScene>();
        sf::Vector2f position = GetPosition();

        scene->AddGuidedProjectile(7, position.x, position.y, sf::Color::White, 180, "PlayerProj", scene->GetClosestEnemy(this), -1000, 500);
        scene->AddGuidedProjectile(7, position.x, position.y, sf::Color::White, 180, "PlayerProj", scene->GetClosestEnemy(this), 0, -1000);
        scene->AddGuidedProjectile(7, position.x, position.y, sf::Color::White, 180, "PlayerProj", scene->GetClosestEnemy(this), 0, 1000);
        scene->AddGuidedProjectile(7, position.x, position.y, sf::Color::White, 180, "PlayerProj", scene->GetClosestEnemy(this), -1000, -500);

        rocketCooldown.Reset();
    }
}
bool Player::GetIsDead() {
    return isDead;
}
void Player::SetIsDead(bool value) {
    isDead = value;
}
void Player::SetFlashed(bool value) {
    isFlashed = value;
}
void Player::AddScore(int value) {
    score += value;
}