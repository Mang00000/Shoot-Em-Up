#include "Pompier.h"
#include "Projectile.h"
#include "GameScene.h"
#include <iostream>
#include "Player.h"
#include "Scene.h"
#include "Entity.h"
#include <cmath>

void Pompier::OnCollision(Entity* other)
{
    if (other->IsTag(1)) {
        mToDestroy = true;
        other->Destroy();
    }
}

void Pompier::OnUpdate()
{
    Player* pPlayer = GetScene<GameScene>()->GetPlayer();
    float playerX = pPlayer->GetPosition().x;
    float playerY = pPlayer->GetPosition().y;

    // Gestion des tirs
    if (cooldown > shotspeed) {
        GetScene<GameScene>()->AddProjectile(3, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 0, projectilespeed);
        cooldown = 0;
    }
    else {
        cooldown += GetDeltaTime();
    }

    // Largeur de la fenêtre
    float windowWidth = GetScene()->GetWindowWidth();

    // Vérifier si on est proche de la cible actuelle en X
    if (std::abs(targetX - GetPosition().x) < 5.0f) {
        targetX = windowWidth * (0.8f + static_cast<float>(rand()) / RAND_MAX * 0.2f); // Nouvelle cible entre 4/5 et 5/5
    }

    // Calcul d'un mouvement fluide en X avec un ralentissement progressif
    float xDelta = targetX - GetPosition().x;
    float xSpeed = std::clamp(std::abs(xDelta) * 0.1f, 10.0f, 50.0f); // Vitesse ajustée selon la distance
    float newX = GetPosition().xq;

    // Vérifier si on est proche de la cible actuelle en Y
    if (std::abs(targetY - GetPosition().y) < 5.0f) {
        targetY = rand() % GetScene()->GetWindowHeight(); // Nouvelle cible aléatoire pour Y
    }

    // Calcul d'un mouvement fluide en Y avec un ralentissement progressif
    float yDelta = targetY - GetPosition().y;
    float ySpeed = std::clamp(std::abs(yDelta) * 0.01f, 10.0f, 50.0f); // Vitesse ajustée selon la distance
    float newY = GetPosition().y + (yDelta > 0 ? ySpeed : -ySpeed) * GetDeltaTime();

    // Appliquer les nouvelles positions
    SetPosition(newX, newY);
}
