#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Cooldown.h"
#include <SFML/Graphics.hpp>

class Player : public Entity {
private:
    // Stats
    struct Stats {
        int hp = 3;
        float projectileSpeed = 580.0f;
        float shotSpeed = 8.2f;
        int projectileSize = 3;
    } stats;

    // Cooldowns
    Cooldown shotCooldown{ 1.0f / stats.shotSpeed };
    Cooldown flashCooldown{ 5.0f };
    Cooldown klaxonCooldown{ 10.0f };
    Cooldown rocketCooldown{ 15.0f };
    Cooldown invincibleCooldown{ 3.0f };

    // Buffs
    bool buffSpeed = false;
    bool buffSize = false;

    // Auto mode (Joue automatiquement les Abilities quand elles sont prête)
    bool autoMode = true;

    // End Game
    bool isDead = false;

    //Player Status / Debuff
    bool isFlashed = false;

    // Score
    int score = 0;

    void DrawCooldownBars();
    void HandleCooldowns();


public:
    // Reset les cooldowns
    Player();
    // Update
    void OnUpdate() override;
    void OnCollision(Entity* other) override;

    // Player abilities
    void Flashing();
    void Klaxon();
    void Rocket();
    void Shoot();

    // Apply buffs
    void ApplyBuff(int wave);

    // Setter Getter
    bool GetIsDead();
    void SetIsDead(bool value);
    void SetFlashed(bool value);
    void AddScore(int value);
};

#endif // PLAYER_H
