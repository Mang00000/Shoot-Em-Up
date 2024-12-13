#include "Camion.h"
#include "Projectile.h"
#include "GameScene.h"
#include <iostream>
#include "Player.h"
#include "Utils.h"
#include "Scene.h"
#include "Boss.h"

void Boss::OnCollision(Entity* other)
{
    if (other->IsTag(1)) {
        hp--;
        other->Destroy();
    }
    if (hp < 1) {
        mToDestroy = true;
    }
}

void Boss::OnUpdate()
{
    HandleCooldowns();

    if (atkPatternCooldown.IsReady()) {
        int randomAtk = rand() % 4 + 1;
        Player* pPlayer = GetScene<GameScene>()->GetPlayer();
        float playerX = pPlayer->GetPosition().x;
        float playerY = pPlayer->GetPosition().y;
        if (randomAtk == 1) {           
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 0, 150*3);
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 10, 150*3);
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -10, 150*3);
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 20, 150*3);
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -20, 150*3);

                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 0, 150 * 3, 90);
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 10, 150 * 3,90);
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -10, 150 * 3,90);
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 20, 150 * 3,90);
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -20, 150 * 3,90);

                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 0, 150 * 3,-90);
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 10, 150 * 3,-90);
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -10, 150 * 3,-90);
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 20, 150 * 3,-90);
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -20, 150 * 3,-90);

                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 0, 150 * 3, 45);
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 10, 150 * 3, 45);
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -10, 150 * 3, 45);
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 20, 150 * 3, 45);
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -20, 150 * 3, 45);

                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 0, 150 * 3, -45);
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 10, 150 * 3, -45);
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -10, 150 * 3, -45);
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 20, 150 * 3, -45);
                GetScene<GameScene>()->AddProjectile(13, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -20, 150 * 3, -45);

        }
        else if (randomAtk == 2) {

                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 0, 130);

                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 10, 130);
                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -10, 130);
                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 20, 130);
                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -20, 130);

                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 15, 120);
                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -15, 120);
                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 5, 120);
                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -5, 120);


                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 10, 130*2);
                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -10, 130*2);
                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 20, 130*2);
                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -20, 130*2);

                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 15, 120*2);
                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -15, 120*2);
                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 5, 120*2);
                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, -5, 120*2);

        }
        else if (randomAtk == 3) {
            for (int i = -180; i < 180; i += 10) {
                GetScene<GameScene>()->AddProjectile(10, GetPosition().x, GetPosition().y, sf::Color::Blue, 0, 0, i, 250);
            }
            for (int i = -180; i < 180; i += 15) {
                GetScene<GameScene>()->AddProjectile(15, GetPosition().x, GetPosition().y, sf::Color::Blue, 0, 0, i, 200);
            }
            for (int i = -180; i < 180; i += 20) {
                GetScene<GameScene>()->AddProjectile(20, GetPosition().x, GetPosition().y, sf::Color::Blue, 0, 0, i, 150);
            }
            for (int i = -180; i < 180; i += 25) {
                GetScene<GameScene>()->AddProjectile(25, GetPosition().x, GetPosition().y, sf::Color::Blue, 0, 0, i, 100);
            }
            for (int i = -180; i < 180; i += 30) {
                GetScene<GameScene>()->AddProjectile(30, GetPosition().x, GetPosition().y, sf::Color::Blue, 0, 0, i, 50);
            }
        }
        else {

                GetScene<GameScene>()->AddProjectile(90, GetPosition().x, GetPosition().y, sf::Color::Blue, playerX, playerY, 0, 180*4);

        }

        atkCooldown.Reset(); atkPatternCooldown.Reset();
        
        
    }
    if (movementPatternCooldown.IsReady()) {
        movementPatternCooldown.Reset();

    }
}
void Boss::HandleCooldowns() {
    float deltaTime = GetDeltaTime();
    atkPatternCooldown.Update(deltaTime);
    movementPatternCooldown.Update(deltaTime);
}